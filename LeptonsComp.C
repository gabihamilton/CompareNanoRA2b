#include "NanoTree.C"
#include "RA2bNtupleV20.C"

bool debug = false;

vector<int> filterLeptons(Float_t* pt, double pt_threshold){

  int n=4;
  vector<int> indices;
  for( int i = 0 ; i < n ; i++ ){
    if( pt[i] > pt_threshold){
      cout << "i: " << i << " pt: " << pt[i] << endl;
      indices.push_back(i);
    }
  }
  return indices;
}

void LeptonsComp(){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  TFile* nano_file = new TFile("~/Downloads/Nano_Summer20UL18_TTJets_Inclusive_585C021C-8088-434F-A0A2-3BE09C1E5FD2.root");
  NanoTree* nano_t = new NanoTree((TTree*)nano_file->Get("Events"));
  TFile* ra2b_file = new TFile("~/Downloads/Summer20UL18_TTJets_Inclusive_10_278_RA2AnalysisTree.root");
  RA2bNtupleV20* ra2b_t = new RA2bNtupleV20((TTree*)ra2b_file->Get("TreeMaker2/PreSelection"));

  char temp[100];
  
  vector<TH1F*> e_pt_ra2b;
  vector<TH1F*> e_pt_nano;
  for( int i = 0 ; i < 4 ; i++ ){
    sprintf(temp,"Electronpt_ra2b%i",i);
    e_pt_ra2b.push_back(new TH1F(temp,";Electron p_T [GeV];Events",50,0,800));
    e_pt_ra2b.back()->SetLineWidth(2);
    e_pt_ra2b.back()->SetLineStyle(1);
    e_pt_ra2b.back()->SetLineColor(2);
    sprintf(temp,"Electronpt_nano%i",i);
    e_pt_nano.push_back(new TH1F(temp,";Electron p_T [GeV];Events",50,0,800));
    e_pt_nano.back()->SetLineWidth(2);
    e_pt_nano.back()->SetLineStyle(2);
    e_pt_nano.back()->SetLineColor(4);
  }

  vector<TH1F*> e_eta_ra2b;
  vector<TH1F*> e_eta_nano;
  for( int i = 0 ; i < 4 ; i++ ){
    sprintf(temp,"Electroneta_ra2b%i",i);
      e_eta_ra2b.push_back(new TH1F(temp,";Electron #eta [GeV];Events",20,-5,5));
      e_eta_ra2b.back()->SetLineWidth(2);
      e_eta_ra2b.back()->SetLineStyle(1);
      e_eta_ra2b.back()->SetLineColor(2);
    sprintf(temp,"Electroneta_nano%i",i);
      e_eta_nano.push_back(new TH1F(temp,";Electron #eta [GeV];Events",20,-5,5));
      e_eta_nano.back()->SetLineWidth(2);
      e_eta_nano.back()->SetLineStyle(2);
      e_eta_nano.back()->SetLineColor(4);
  }
    
    vector<TH1F*> e_phi_ra2b;
    vector<TH1F*> e_phi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Electronphi_ra2b%i",i);
        e_phi_ra2b.push_back(new TH1F(temp,";Electron #phi [GeV];Events",20,-5,5));
        e_phi_ra2b.back()->SetLineWidth(2);
        e_phi_ra2b.back()->SetLineStyle(1);
        e_phi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Electronphi_nano%i",i);
        e_phi_nano.push_back(new TH1F(temp,";Electron #phi [GeV];Events",20,-5,5));
        e_phi_nano.back()->SetLineWidth(2);
        e_phi_nano.back()->SetLineStyle(2);
        e_phi_nano.back()->SetLineColor(4);
    }
    
    //MUONS
    
    vector<TH1F*> mu_pt_ra2b;
    vector<TH1F*> mu_pt_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Muonpt_ra2b%i",i);
        mu_pt_ra2b.push_back(new TH1F(temp,";Muon p_T [GeV];Events",50,0,800));
        mu_pt_ra2b.back()->SetLineWidth(2);
        mu_pt_ra2b.back()->SetLineStyle(1);
        mu_pt_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Muonpt_nano%i",i);
        mu_pt_nano.push_back(new TH1F(temp,";Muon p_T [GeV];Events",50,0,800));
        mu_pt_nano.back()->SetLineWidth(2);
        mu_pt_nano.back()->SetLineStyle(2);
        mu_pt_nano.back()->SetLineColor(4);
    }

    vector<TH1F*> mu_eta_ra2b;
    vector<TH1F*> mu_eta_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Muoneta_ra2b%i",i);
        mu_eta_ra2b.push_back(new TH1F(temp,";Muon #eta [GeV];Events",20,-5,5));
        mu_eta_ra2b.back()->SetLineWidth(2);
        mu_eta_ra2b.back()->SetLineStyle(1);
        mu_eta_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Muoneta_nano%i",i);
        mu_eta_nano.push_back(new TH1F(temp,";Muon #eta [GeV];Events",20,-5,5));
        mu_eta_nano.back()->SetLineWidth(2);
        mu_eta_nano.back()->SetLineStyle(2);
        mu_eta_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> mu_phi_ra2b;
    vector<TH1F*> mu_phi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Muonphi_ra2b%i",i);
        mu_phi_ra2b.push_back(new TH1F(temp,";Muon #phi [GeV];Events",20,-5,5));
        mu_phi_ra2b.back()->SetLineWidth(2);
        mu_phi_ra2b.back()->SetLineStyle(1);
        mu_phi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Muonphi_nano%i",i);
        mu_phi_nano.push_back(new TH1F(temp,";Muon #phi [GeV];Events",20,-5,5));
        mu_phi_nano.back()->SetLineWidth(2);
        mu_phi_nano.back()->SetLineStyle(2);
        mu_phi_nano.back()->SetLineColor(4);
    }
    
    //PHOTONS
    
    vector<TH1F*> pho_pt_ra2b;
    vector<TH1F*> pho_pt_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photonpt_ra2b%i",i);
        pho_pt_ra2b.push_back(new TH1F(temp,";Photon p_T [GeV];Events",50,0,800));
        pho_pt_ra2b.back()->SetLineWidth(2);
        pho_pt_ra2b.back()->SetLineStyle(1);
        pho_pt_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photonpt_nano%i",i);
        pho_pt_nano.push_back(new TH1F(temp,";Photon p_T [GeV];Events",50,0,800));
        pho_pt_nano.back()->SetLineWidth(2);
        pho_pt_nano.back()->SetLineStyle(2);
        pho_pt_nano.back()->SetLineColor(4);
    }

    vector<TH1F*> pho_eta_ra2b;
    vector<TH1F*> pho_eta_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photoneta_ra2b%i",i);
        pho_eta_ra2b.push_back(new TH1F(temp,";Photon #eta [GeV];Events",20,-5,5));
        pho_eta_ra2b.back()->SetLineWidth(2);
        pho_eta_ra2b.back()->SetLineStyle(1);
        pho_eta_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photoneta_nano%i",i);
        pho_eta_nano.push_back(new TH1F(temp,";Photon #eta [GeV];Events",20,-5,5));
        pho_eta_nano.back()->SetLineWidth(2);
        pho_eta_nano.back()->SetLineStyle(2);
        pho_eta_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> pho_phi_ra2b;
    vector<TH1F*> pho_phi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photonphi_ra2b%i",i);
        pho_phi_ra2b.push_back(new TH1F(temp,";Photon #phi [GeV];Events",20,-5,5));
        pho_phi_ra2b.back()->SetLineWidth(2);
        pho_phi_ra2b.back()->SetLineStyle(1);
        pho_phi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photonphi_nano%i",i);
        pho_phi_nano.push_back(new TH1F(temp,";Photon #phi [GeV];Events",20,-5,5));
        pho_phi_nano.back()->SetLineWidth(2);
        pho_phi_nano.back()->SetLineStyle(2);
        pho_phi_nano.back()->SetLineColor(4);
    }

    

  int numEvents = ra2b_t->fChain->GetEntriesFast();
  for( int evt = 0 ; evt < numEvents ; evt++ ){
    if(debug) cout << "event: " << evt << endl;
    ra2b_t->GetEntry(evt);
    nano_t->GetEntry(numEvents-evt-1);

    //cout << "ra2" << endl;
    vector<int> ra2b_indices_e = filterLeptons(ra2b_t->Electrons_fCoordinates_fPt, 10.0);
    //cout << "nano" << endl;
    vector<int> nano_indices_e = filterLeptons(nano_t->Electron_pt, 10.0);
      vector<int> ra2b_indices_m = filterLeptons(ra2b_t->Muons_fCoordinates_fPt, 10.0);
      vector<int> nano_indices_m = filterLeptons(nano_t->Muon_pt, 10.0);
      vector<int> ra2b_indices_p = filterLeptons(ra2b_t->Photons_fCoordinates_fPt, 30.0);
      vector<int> nano_indices_p = filterLeptons(nano_t->Photon_pt, 30.0);

    //cout << "num good jets :: ra2b " << ra2b_indices.size() << " nano " << nano_indices.size() << endl;
    
    for( int j= 0 ; j < 4 ; j++ ){
      if( j < ra2b_indices_e.size() ){
        e_pt_ra2b[j]->Fill(ra2b_t->Electrons_fCoordinates_fPt[ra2b_indices_e[j]]);
        e_eta_ra2b[j]->Fill(ra2b_t->Electrons_fCoordinates_fEta[ra2b_indices_e[j]]);
        e_phi_ra2b[j]->Fill(ra2b_t->Electrons_fCoordinates_fPhi[ra2b_indices_e[j]]);
      }if( j < nano_indices_e.size() ){
        e_pt_nano[j]->Fill(nano_t->Electron_pt[nano_indices_e[j]]);
        e_eta_nano[j]->Fill(nano_t->Electron_eta[nano_indices_e[j]]);
        e_phi_nano[j]->Fill(nano_t->Electron_phi[nano_indices_e[j]]);
      }
        if(j< ra2b_indices_m.size()){
          mu_pt_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fPt[ra2b_indices_m[j]]);
          mu_eta_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fEta[ra2b_indices_m[j]]);
          mu_phi_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fPhi[ra2b_indices_m[j]]);
        }
        if(j< nano_indices_m.size()){
            mu_pt_nano[j]->Fill(nano_t->Muon_pt[nano_indices_m[j]]);
            mu_eta_nano[j]->Fill(nano_t->Muon_eta[nano_indices_m[j]]);
            mu_phi_nano[j]->Fill(nano_t->Muon_phi[nano_indices_m[j]]);
        }
        
        if(j<ra2b_indices_p.size()){
          pho_pt_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fPt[ra2b_indices_p[j]]);
          pho_eta_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fEta[ra2b_indices_p[j]]);
          pho_phi_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fPhi[ra2b_indices_p[j]]);
        }
        if(j<nano_indices_p.size()){
          pho_pt_nano[j]->Fill(nano_t->Photon_pt[nano_indices_p[j]]);
          pho_eta_nano[j]->Fill(nano_t->Photon_eta[nano_indices_p[j]]);
          pho_phi_nano[j]->Fill(nano_t->Photon_phi[nano_indices_p[j]]);
        }
    }
      
  }

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetLogy();

  for( int j= 0 ; j < 4 ; j++ ){
    sprintf(temp,"filteredElectron_pt%i.png",j);
    e_pt_ra2b[j]->Draw();
    e_pt_nano[j]->Draw("SAME");
    can->SaveAs(temp);

    sprintf(temp,"filteredElectron_eta%i.png",j);
    e_eta_ra2b[j]->Draw();
    e_eta_nano[j]->Draw("SAME");
    can->SaveAs(temp);
      
    sprintf(temp,"filteredElectron_phi%i.png",j);
    e_phi_ra2b[j]->Draw();
    e_phi_nano[j]->Draw("SAME");
    can->SaveAs(temp);

      
      sprintf(temp,"filteredMuon_pt%i.png",j);
      mu_pt_ra2b[j]->Draw();
      mu_pt_nano[j]->Draw("SAME");
      can->SaveAs(temp);

      sprintf(temp,"filteredMuon_eta%i.png",j);
      mu_eta_ra2b[j]->Draw();
      mu_eta_nano[j]->Draw("SAME");
      can->SaveAs(temp);
        
      sprintf(temp,"filteredMuon_phi%i.png",j);
      mu_phi_ra2b[j]->Draw();
      mu_phi_nano[j]->Draw("SAME");
      can->SaveAs(temp);
      
      sprintf(temp,"filteredPhoton_pt%i.png",j);
      pho_pt_ra2b[j]->Draw();
      pho_pt_nano[j]->Draw("SAME");
      can->SaveAs(temp);

      sprintf(temp,"filteredPhoton_eta%i.png",j);
      pho_eta_ra2b[j]->Draw();
      pho_eta_nano[j]->Draw("SAME");
      can->SaveAs(temp);
        
      sprintf(temp,"filteredPhoton_phi%i.png",j);
      pho_phi_ra2b[j]->Draw();
      pho_phi_nano[j]->Draw("SAME");
      can->SaveAs(temp);
  }
  
}
