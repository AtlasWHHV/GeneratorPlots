#ifndef __lifetime_plots__
#define __lifetime_plots__

#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthVertex.h"
#include <EventLoop/Worker.h>

#include "TH1F.h"
#include "TH2F.h"

#include <string>

using namespace std;

class lifetime_plots {
  public:
    // Book the plots
    lifetime_plots (const std::string &name, const std::string &title, EL::Worker *wk)
    {
      _deltaT = new TH1F((name + "DeltaT").c_str(), (title + " Delta t; t_{dec} - t_{prod} [ns]").c_str(),260,-6,20);
      wk->addOutput (_deltaT);
    }

    // Fill the plots.
    void Process(const xAOD::TruthParticle *p) 
    {
      if (p->hasProdVtx() && p->hasDecayVtx())
      {
        _deltaT->Fill(p->decayVtx()->v4().T()*0.001 - p->prodVtx()->v4().T()*0.001);
        if ( (p->decayVtx()->v4().T()*0.001 - p->prodVtx()->v4().T()*0.001)<0 )
        {
          cout << " - Decay = " << p->decayVtx()->v4().T()*0.001 << endl;
          cout << " - Prod  = " << p->prodVtx()->v4().T()*0.001 << endl;
          cout << "         -- diff = " << p->decayVtx()->v4().T()*0.001 - p->prodVtx()->v4().T()*0.001 << endl;	
        }
      }
    }

  private:
    TH1F *_deltaT;
};

#endif
