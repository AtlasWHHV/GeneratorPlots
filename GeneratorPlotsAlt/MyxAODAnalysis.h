#ifndef GeneratorPlotsAlt_MyxAODAnalysis_H
#define GeneratorPlotsAlt_MyxAODAnalysis_H

#include <EventLoop/Algorithm.h>

#include "GeneratorPlotsAlt/lepton_plots.h"
#include "GeneratorPlotsAlt/two_particle_plots.h"
#include "GeneratorPlotsAlt/standard_p_plots.h"
#include "GeneratorPlotsAlt/lifetime_plots.h"
#include "GeneratorPlotsAlt/truth_helpers.h"

class MyxAODAnalysis : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
  int m_eventCounter; //!

  // Histograms for each type of particle.
  lifetime_plots*       all; //!
  standard_p_plots*     hs; //!
  standard_p_plots*     w; //!
  two_particle_plots*   twohs; //!
  lepton_plots*	        e_neutrino; //!
  lepton_plots*         mu_neutrino; //!
  lepton_plots*	        e; //!
  lepton_plots*	        mu; //!
  two_particle_plots*   w_decays; //!

  // this is a standard constructor
  MyxAODAnalysis ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(MyxAODAnalysis, 1);
};

#endif
