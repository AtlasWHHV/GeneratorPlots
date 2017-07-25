#ifndef __two_particle_plots__
#define __two_particle_plots__

#include "xAODTruth/TruthParticle.h"
#include "TH1.h"
#include <EventLoop/Worker.h>

#include <string>

class two_particle_plots {
 public:

  two_particle_plots(const std::string &name, const std::string &title, EL::Worker *wk, bool leptons)
  {
    _leptons = leptons;
    _deltaR       = new TH1F ((name + "DR"  ).c_str(),     (title + "\\Delta R; \\Delta R").c_str(), 100, 0.0, 5.0);
    wk->addOutput (_deltaR);
    _deltaPhi     = new TH1F ((name + "Dphi").c_str(),     (title + "|\\Delta \\phi|; |\\Delta \\phi|").c_str(), 100, 0, 3.5);
    wk->addOutput (_deltaPhi);
    _deltaEta     = new TH1F ((name + "Deta").c_str(),     (title + "|\\Delta \\eta|; |\\Delta \\eta|").c_str(), 100, 0, 3.0 );
    wk->addOutput (_deltaEta);
    if (leptons)
    {
      _deltaR_e     = new TH1F ((name + "DR_e"  ).c_str(),   (title + "\\Delta R  electrons; \\Delta R  electrons").c_str(), 100, 0.0, 5.0);
      wk->addOutput (_deltaR_e);
      _deltaPhi_e   = new TH1F ((name + "Dphi_e").c_str(),   (title + "|\\Delta \\phi|  electrons; |\\Delta \\phi|  electrons").c_str(), 100, 0, 3.5);
      wk->addOutput (_deltaPhi_e);
      _deltaEta_e   = new TH1F ((name + "Deta_e").c_str(),   (title + "|\\Delta \\eta|  electrons; |\\Delta \\eta|  electrons").c_str(), 100, 0, 3.0 );
      wk->addOutput (_deltaEta_e);
      _deltaR_mu    = new TH1F ((name + "DR_mu"  ).c_str(),  (title + "\\Delta R  muons; \\Delta R  muons").c_str(), 100, 0.0, 5.0);
      wk->addOutput (_deltaR_mu);
      _deltaPhi_mu  = new TH1F ((name + "Dphi_mu").c_str(),  (title + "|\\Delta \\phi|  muons; |\\Delta \\phi|  muons").c_str(), 100, 0, 3.5);
      wk->addOutput (_deltaPhi_mu);
      _deltaEta_mu  = new TH1F ((name + "Deta_mu").c_str(),  (title + "|\\Delta \\eta|  muons; |\\Delta \\eta|  muons").c_str(), 100, 0, 3.0 );
      wk->addOutput (_deltaEta_mu);
    }
  }

  void addParticle (const xAOD::TruthParticle *p)
  {
    _stash.push_back(p);
  }

  // This is where the work happens
  void EndOfEvent()
  {
    if (_stash.size() < 2) {
      _stash.clear();
      return;
    }


    // Calculate delta R, delta Phi, and delta Eta for the two particles.
    auto h1 = _stash[0]->p4();
    auto h2 = _stash[1]->p4();
    auto deltaR = h1.DeltaR(h2);
    auto deltaPhi = h1.DeltaPhi(h2);
    auto deltaEta = fabs(h1.Eta() - h2.Eta());

    // Fill the corresponding histograms.
    _deltaR->Fill(deltaR);
    _deltaPhi->Fill(deltaPhi);
    _deltaEta->Fill(deltaEta);
    // If leptons is true, then fill the correct lepton histograms.
    if (_leptons)
    {
      // Check the ID of the first particle, and assume the second is correct.
      auto id = _stash[0]->absPdgId();
      if (id == 11 || id == 12) // 11 is the electron, 12 is the neutrino.
      {
        _deltaR_e->Fill(deltaR);
        _deltaPhi_e->Fill(deltaPhi);
        _deltaEta_e->Fill(deltaEta);
      }
      else if (id == 13 || id == 14) // 13 is the muon, 14 is the neutrino.
      {
        _deltaR_mu->Fill(deltaR);
        _deltaPhi_mu->Fill(deltaPhi);
        _deltaEta_mu->Fill(deltaEta);
      }
      else
      {
        Error("two_particle_plots::EndOfEvent()", "Unexpected particle added when _leptons was true.");
      }
    }
    _stash.clear();
  }

 private:
  std::vector<const xAOD::TruthParticle *> _stash;
  bool _leptons;
  TH1F *_deltaR;
  TH1F *_deltaPhi;
  TH1F *_deltaEta;
  TH1F *_deltaR_e;
  TH1F *_deltaPhi_e;
  TH1F *_deltaEta_e;
  TH1F *_deltaR_mu;
  TH1F *_deltaPhi_mu;
  TH1F *_deltaEta_mu;
};

#endif
