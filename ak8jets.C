#include "NanoTree.C"
#include "RA2bNtupleV20.C"

bool debug = false;

vector<int> filterLeptons(Float_t* pt){

  int n=4;
  double pt_threshold=30.;
  vector<int> indices;
  for( int i = 0 ; i < n ; i++ ){
    if( pt[i] > pt_threshold){
      cout << "i: " << i << " pt: " << pt[i] << endl;
      indices.push_back(i);
    }
  }
  return indices;
}

void ak8jets(){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  TFile* nano_file = new TFile("~/Downloads/Nano_Summer20UL18_TTJets_Inclusive_585C021C-8088-434F-A0A2-3BE09C1E5FD2.root");
  NanoTree* nano_t = new NanoTree((TTree*)nano_file->Get("Events"));
  TFile* ra2b_file = new TFile("~/Downloads/Summer20UL18_TTJets_Inclusive_10_278_RA2AnalysisTree.root");
  RA2bNtupleV20* ra2b_t = new RA2bNtupleV20((TTree*)ra2b_file->Get("TreeMaker2/PreSelection"));

  char temp[100];
  
  vector<TH1F*> jetpt_ra2b;
  vector<TH1F*> jetpt_nano;
  for( int i = 0 ; i < 4 ; i++ ){
    sprintf(temp,"Electronpt_ra2b%i",i);
    jetpt_ra2b.push_back(new TH1F(temp,";Electron p_T [GeV];Events",50,0,800));
    jetpt_ra2b.back()->SetLineWidth(2);
    jetpt_ra2b.back()->SetLineStyle(1);
    jetpt_ra2b.back()->SetLineColor(2);
    sprintf(temp,"Electronpt_nano%i",i);
    jetpt_nano.push_back(new TH1F(temp,";Electron p_T [GeV];Events",50,0,800));
    jetpt_nano.back()->SetLineWidth(2);
    jetpt_nano.back()->SetLineStyle(2);
    jetpt_nano.back()->SetLineColor(4);
  }

  vector<TH1F*> jetptdiff;
  for( int i = 0 ; i < 4 ; i++ ){
    sprintf(temp,"Electronptdiff%i",i);
    jetptdiff.push_back(new TH1F(temp,"; Electron #Delta p_T [GeV];Events",50,-200,200));
    jetptdiff.back()->SetLineWidth(2);
    jetptdiff.back()->SetLineStyle(1);
    jetptdiff.back()->SetLineColor(2);
  }

  vector<TH1F*> jeteta_ra2b;
  vector<TH1F*> jeteta_nano;
  for( int i = 0 ; i < 4 ; i++ ){
    sprintf(temp,"Electroneta_ra2b%i",i);
    jeteta_ra2b.push_back(new TH1F(temp,";Electron #eta [GeV];Events",20,-5,5));
    jeteta_ra2b.back()->SetLineWidth(2);
    jeteta_ra2b.back()->SetLineStyle(1);
    jeteta_ra2b.back()->SetLineColor(2);
    sprintf(temp,"Electroneta_nano%i",i);
    jeteta_nano.push_back(new TH1F(temp,";Electron #eta [GeV];Events",20,-5,5));
    jeteta_nano.back()->SetLineWidth(2);
    jeteta_nano.back()->SetLineStyle(2);
    jeteta_nano.back()->SetLineColor(4);
  }
    
    vector<TH1F*> jetphi_ra2b;
    vector<TH1F*> jetphi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Electronphi_ra2b%i",i);
      jetphi_ra2b.push_back(new TH1F(temp,";Electron #phi [GeV];Events",20,-5,5));
      jetphi_ra2b.back()->SetLineWidth(2);
      jetphi_ra2b.back()->SetLineStyle(1);
      jetphi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Electronphi_nano%i",i);
      jetphi_nano.push_back(new TH1F(temp,";Electron #phi [GeV];Events",20,-5,5));
      jetphi_nano.back()->SetLineWidth(2);
      jetphi_nano.back()->SetLineStyle(2);
      jetphi_nano.back()->SetLineColor(4);
    }
    
    //MUONS
    
    vector<TH1F*> mupt_ra2b;
    vector<TH1F*> mupt_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Muonpt_ra2b%i",i);
        mupt_ra2b.push_back(new TH1F(temp,";Muon p_T [GeV];Events",50,0,800));
        mupt_ra2b.back()->SetLineWidth(2);
        mupt_ra2b.back()->SetLineStyle(1);
        mupt_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Muonpt_nano%i",i);
        mupt_nano.push_back(new TH1F(temp,";Muon p_T [GeV];Events",50,0,800));
        mupt_nano.back()->SetLineWidth(2);
        mupt_nano.back()->SetLineStyle(2);
        mupt_nano.back()->SetLineColor(4);
    }

    vector<TH1F*> mueta_ra2b;
    vector<TH1F*> mueta_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Muoneta_ra2b%i",i);
        mueta_ra2b.push_back(new TH1F(temp,";Muon #eta [GeV];Events",20,-5,5));
        mueta_ra2b.back()->SetLineWidth(2);
        mueta_ra2b.back()->SetLineStyle(1);
        mueta_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Muoneta_nano%i",i);
        mueta_nano.push_back(new TH1F(temp,";Muon #eta [GeV];Events",20,-5,5));
        mueta_nano.back()->SetLineWidth(2);
        mueta_nano.back()->SetLineStyle(2);
        mueta_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> muphi_ra2b;
    vector<TH1F*> muphi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Muonphi_ra2b%i",i);
        muphi_ra2b.push_back(new TH1F(temp,";Muon #phi [GeV];Events",20,-5,5));
        muphi_ra2b.back()->SetLineWidth(2);
        muphi_ra2b.back()->SetLineStyle(1);
        muphi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Muonphi_nano%i",i);
        muphi_nano.push_back(new TH1F(temp,";Muon #phi [GeV];Events",20,-5,5));
        muphi_nano.back()->SetLineWidth(2);
        muphi_nano.back()->SetLineStyle(2);
        muphi_nano.back()->SetLineColor(4);
    }
    
    //PHOTONS
    
    vector<TH1F*> phopt_ra2b;
    vector<TH1F*> phopt_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photonpt_ra2b%i",i);
        phopt_ra2b.push_back(new TH1F(temp,";Photon p_T [GeV];Events",50,0,800));
        phopt_ra2b.back()->SetLineWidth(2);
        phopt_ra2b.back()->SetLineStyle(1);
        phopt_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photonpt_nano%i",i);
        phopt_nano.push_back(new TH1F(temp,";Photon p_T [GeV];Events",50,0,800));
        phopt_nano.back()->SetLineWidth(2);
        phopt_nano.back()->SetLineStyle(2);
        phopt_nano.back()->SetLineColor(4);
    }

    vector<TH1F*> phoeta_ra2b;
    vector<TH1F*> phoeta_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photoneta_ra2b%i",i);
        phoeta_ra2b.push_back(new TH1F(temp,";Photon #eta [GeV];Events",20,-5,5));
        phoeta_ra2b.back()->SetLineWidth(2);
        phoeta_ra2b.back()->SetLineStyle(1);
        phoeta_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photoneta_nano%i",i);
        phoeta_nano.push_back(new TH1F(temp,";Photon #eta [GeV];Events",20,-5,5));
        phoeta_nano.back()->SetLineWidth(2);
        phoeta_nano.back()->SetLineStyle(2);
        phoeta_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> phophi_ra2b;
    vector<TH1F*> phophi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photonphi_ra2b%i",i);
        phophi_ra2b.push_back(new TH1F(temp,";Photon #phi [GeV];Events",20,-5,5));
        phophi_ra2b.back()->SetLineWidth(2);
        phophi_ra2b.back()->SetLineStyle(1);
        phophi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photonphi_nano%i",i);
        phophi_nano.push_back(new TH1F(temp,";Photon #phi [GeV];Events",20,-5,5));
        phophi_nano.back()->SetLineWidth(2);
        phophi_nano.back()->SetLineStyle(2);
        phophi_nano.back()->SetLineColor(4);
    }

    

  int numEvents = ra2b_t->fChain->GetEntriesFast();
  for( int evt = 0 ; evt < numEvents ; evt++ ){
    if(debug) cout << "event: " << evt << endl;
    ra2b_t->GetEntry(evt);
    nano_t->GetEntry(numEvents-evt-1);

    //cout << "ra2" << endl;
    vector<int> ra2b_indices = filterLeptons(ra2b_t->Electrons_fCoordinates_fPt);
    //cout << "nano" << endl;
    vector<int> nano_indices = filterLeptons(nano_t->Electron_pt);

    //cout << "num good jets :: ra2b " << ra2b_indices.size() << " nano " << nano_indices.size() << endl;
    
    for( int j= 0 ; j < 4 ; j++ ){
      if( j < ra2b_indices.size() ){
	jetpt_ra2b[j]->Fill(ra2b_t->Electrons_fCoordinates_fPt[ra2b_indices[j]]);
	jeteta_ra2b[j]->Fill(ra2b_t->Electrons_fCoordinates_fEta[ra2b_indices[j]]);
    jetphi_ra2b[j]->Fill(ra2b_t->Electrons_fCoordinates_fPhi[ra2b_indices[j]]);
          mupt_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fPt[ra2b_indices[j]]);
          mueta_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fEta[ra2b_indices[j]]);
          muphi_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fPhi[ra2b_indices[j]]);
          phopt_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fPt[ra2b_indices[j]]);
          phoeta_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fEta[ra2b_indices[j]]);
          phophi_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fPhi[ra2b_indices[j]]);
      }if( j < nano_indices.size() ){
	jetpt_nano[j]->Fill(nano_t->Electron_pt[nano_indices[j]]);
	jeteta_nano[j]->Fill(nano_t->Electron_eta[nano_indices[j]]);
    jetphi_nano[j]->Fill(nano_t->Electron_phi[nano_indices[j]]);
          mupt_nano[j]->Fill(nano_t->Muon_pt[nano_indices[j]]);
          mueta_nano[j]->Fill(nano_t->Muon_eta[nano_indices[j]]);
          muphi_nano[j]->Fill(nano_t->Muon_phi[nano_indices[j]]);
          phopt_nano[j]->Fill(nano_t->Photon_pt[nano_indices[j]]);
          phoeta_nano[j]->Fill(nano_t->Photon_eta[nano_indices[j]]);
          phophi_nano[j]->Fill(nano_t->Photon_phi[nano_indices[j]]);
      }if( j < nano_indices.size() && j < ra2b_indices.size() ){
	jetptdiff[j]->Fill( ra2b_t->JetsAK8_fCoordinates_fPt[ra2b_indices[j]] - nano_t->FatJet_pt[nano_indices[j]] );
      }
      
    }

  }

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetLogy();

  for( int j= 0 ; j < 4 ; j++ ){
    sprintf(temp,"filteredElectron_pt%i.png",j);
    jetpt_ra2b[j]->Draw();
    jetpt_nano[j]->Draw("SAME");
    can->SaveAs(temp);

    sprintf(temp,"filteredElectron_eta%i.png",j);
    jeteta_ra2b[j]->Draw();
    jeteta_nano[j]->Draw("SAME");
    can->SaveAs(temp);
      
    sprintf(temp,"filteredElectron_phi%i.png",j);
    jetphi_ra2b[j]->Draw();
    jetphi_nano[j]->Draw("SAME");
    can->SaveAs(temp);

    sprintf(temp,"filteredElectron_ptdiff%i.png",j);
    jetptdiff[j]->Draw();
    can->SaveAs(temp);
      
      sprintf(temp,"filteredMuon_pt%i.png",j);
      mupt_ra2b[j]->Draw();
      mupt_nano[j]->Draw("SAME");
      can->SaveAs(temp);

      sprintf(temp,"filteredMuon_eta%i.png",j);
      mueta_ra2b[j]->Draw();
      mueta_nano[j]->Draw("SAME");
      can->SaveAs(temp);
        
      sprintf(temp,"filteredMuon_phi%i.png",j);
      muphi_ra2b[j]->Draw();
      muphi_nano[j]->Draw("SAME");
      can->SaveAs(temp);
      
      sprintf(temp,"filteredPhoton_pt%i.png",j);
      phopt_ra2b[j]->Draw();
      phopt_nano[j]->Draw("SAME");
      can->SaveAs(temp);

      sprintf(temp,"filteredPhoton_eta%i.png",j);
      phoeta_ra2b[j]->Draw();
      phoeta_nano[j]->Draw("SAME");
      can->SaveAs(temp);
        
      sprintf(temp,"filteredPhoton_phi%i.png",j);
      phophi_ra2b[j]->Draw();
      phophi_nano[j]->Draw("SAME");
      can->SaveAs(temp);
  }
  
}
