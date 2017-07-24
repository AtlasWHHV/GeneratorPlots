#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <GeneratorPlotsAlt/MyxAODAnalysis.h>

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"

// Gordoncode
#include "xAODTruth/TruthEventContainer.h"
#include "GeneratorPlotsAlt/truth_helpers.h"

// ASG status code check
#include <AsgTools/MessageCheck.h>

// EDM includes:
#include "xAODEventInfo/EventInfo.h"

// To create a basic loop over a jet container, for the AntiKt4EMTTopoJets jet collection.
#include "xAODJet/JetContainer.h"

// Validation histograms:
#include "GeneratorPlotsAlt/lepton_plots.h"
#include "GeneratorPlotsAlt/two_particle_plots.h"
#include "GeneratorPlotsAlt/standard_p_plots.h"
#include "GeneratorPlotsAlt/lifetime_plots.h"
#include "GeneratorPlotsAlt/truth_helpers.h"

// Config
const char *APP_NAME = "validationPlots";
const char *OutputFile = "validation.root";

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODAnalysis)



MyxAODAnalysis :: MyxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode MyxAODAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  // let's initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  ANA_CHECK(xAOD::Init());

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // This method is called before processing any events. Note that the wk()->addOutput call is a mechanism EventLoop uses for delivering the results of an algorithm to the outside world. When running in PROOF, ROOT will merge all of the objects in this list.

  // Initializing histograms
  all = new lifetime_plots ("all", "all ", wk());
  hs = new standard_p_plots ("hs", "#h_{s} ", wk());
  twohs = new two_particle_plots ("twoHS", "Two HSs ", wk());
  e_neutrino = new lepton_plots ("e_neutrino_", "\\nu_{e} ", wk(), false);
  mu_neutrino = new lepton_plots ("mu_neutrino_", "\\nu_{\\mu} ", wk(), false);
  e = new lepton_plots ("e_", "e ", wk(), true);
  mu = new lepton_plots ("mu_", "\\mu ", wk(), true);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  (void)firstFile; // Suppress unused-variable warning. 
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  xAOD::TEvent* event = wk()->xaodEvent();

  // as a check, let's see the number of events in our xAOD
  Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  // count number of events
  m_eventCounter = 0;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  xAOD::TEvent* event = wk()->xaodEvent();

  // print every 100 events, so we know where we are:
  if ((m_eventCounter % 100) == 0) 
  {
    Info("execute()", "Event number = %i", m_eventCounter);
  }
  m_eventCounter++;

  // Get the truth events.
  const xAOD::TruthEventContainer *truth = nullptr;
  ANA_CHECK(event->retrieve( truth, "TruthEvents"));
  // Loop over all of the truth events.
  for (auto evt : *truth) 
  {
    for (auto p : truth_as_range(evt)) 
    {
      if (p != nullptr) 
      {
        all->Process(p);
        if (p->absPdgId() == 35) // 35 is the Higgs' PDG id.
        {
          hs->Process(p);
          twohs->addParticle(p);
        }
        else
        {
          // Check to see if the particle was the result of a W decay.
          bool WDecay = false;
          for (int i = 0; i < p->nParents(); i++)
          {
            auto parent = p->parent(i);
            if (parent->absPdgId() == 24) // 24 is the W+.
            {
              WDecay = true;
              break;
            }
          }
          if (WDecay)
          {
            if (p->absPdgId() == 11) // 11 is the electron.
            {
              e->Process(p);
            }
            else if (p->absPdgId() == 12) // 12 is the electron neutrino.
            {
              e_neutrino->Process(p);
            }
            else if (p->absPdgId() == 13) // 13 is the muon.
            {
              mu->Process(p);
            }
            else if (p->absPdgId() == 14) // 14 is the muon neutrino.
            {
              mu_neutrino->Process(p);
            }
          }
        }
      }
    }
  }
  twohs->EndOfEvent();
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}
