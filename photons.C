#include "NanoTree.C"
#include "RA2bNtupleV20.C"

bool debug = true;

vector<int> filterLeptons(UInt_t number, Float_t* pt, double pt_threshold/*, Float_t* eta, double eta_threshold*/){

    int n=4;
    vector<int> indices;
    for( int i = 0 ; i < n ; i++ ){
        if( number>0 && pt[i] > pt_threshold /*&& fabs(eta[i]) < 2*/){
              //cout << "i: " << i << " pt: " << pt[i] << endl;
              indices.push_back(i);
        }
    }
    return indices;
}


std::string decimalToBinary(int decimalNum) {
    std::string binaryNum = "";

    while (decimalNum > 0) {
        int remainder = decimalNum % 2;
        binaryNum = std::to_string(remainder) + binaryNum;
        decimalNum /= 2;
    }

    return binaryNum;
}

Bool_t vetoBinaryElectron(Int_t bit){
    std::string binary = "";
    binary = decimalToBinary(bit);
        if(binary.size()<30 || binary.substr(27, 3)=="000" || binary.substr(24, 3)=="000" || binary.substr(18, 3)=="000" || binary.substr(15, 3)=="000" || binary.substr(12, 3)=="000" || binary.substr(9, 3)=="000" || binary.substr(6, 3)=="000" || binary.substr(3, 3)=="000"){
            return false;
        }
        else return true;
        
}

vector<int> filterElectron(Int_t* bitmap, Float_t* pt, double pt_threshold){
    int n=4;
    vector<int> indices;
    for( int i = 0 ; i < n ; i++ ){
        //cout << bitmap[i] <<endl;
        if(pt[i] > pt_threshold && vetoBinaryElectron(bitmap[i])/*&& fabs(eta[i]) < 2*/){
              //cout << "i: " << i << " pt: " << pt[i] << endl;
              indices.push_back(i);
        }
    }
    return indices;

}


void photons(){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  TFile* nano_file = new TFile("~/Downloads/Nano_Summer20UL18_TTJets_Inclusive_585C021C-8088-434F-A0A2-3BE09C1E5FD2.root");
  NanoTree* nano_t = new NanoTree((TTree*)nano_file->Get("Events"));
  TFile* ra2b_file = new TFile("~/Downloads/Summer20UL18_TTJets_Inclusive_10_278_RA2AnalysisTree.root");
  RA2bNtupleV20* ra2b_t = new RA2bNtupleV20((TTree*)ra2b_file->Get("TreeMaker2/PreSelection"));

  char temp[100];
  
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
        pho_eta_ra2b.push_back(new TH1F(temp,";Photon #eta [GeV];Events",50,-5,5));
        pho_eta_ra2b.back()->SetLineWidth(2);
        pho_eta_ra2b.back()->SetLineStyle(1);
        pho_eta_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photoneta_nano%i",i);
        pho_eta_nano.push_back(new TH1F(temp,";Photon #eta [GeV];Events",50,-5,5));
        pho_eta_nano.back()->SetLineWidth(2);
        pho_eta_nano.back()->SetLineStyle(2);
        pho_eta_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> pho_phi_ra2b;
    vector<TH1F*> pho_phi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
      sprintf(temp,"Photonphi_ra2b%i",i);
        pho_phi_ra2b.push_back(new TH1F(temp,";Photon #phi [GeV];Events",50,-5,5));
        pho_phi_ra2b.back()->SetLineWidth(2);
        pho_phi_ra2b.back()->SetLineStyle(1);
        pho_phi_ra2b.back()->SetLineColor(2);
      sprintf(temp,"Photonphi_nano%i",i);
        pho_phi_nano.push_back(new TH1F(temp,";Photon #phi [GeV];Events",50,-5,5));
        pho_phi_nano.back()->SetLineWidth(2);
        pho_phi_nano.back()->SetLineStyle(2);
        pho_phi_nano.back()->SetLineColor(4);
    }

  int numEvents = ra2b_t->fChain->GetEntriesFast();
    //cout << numEvents << endl;
  for( int evt = 0 ; evt < numEvents ; evt++ ){
      if(debug) cout << "event: " << numEvents-evt-1 << endl;//evt << endl;
    ra2b_t->GetEntry(evt);
    nano_t->GetEntry(numEvents-evt-1);

      
      
    //vector<int> nano_indices_e = filterElectron(nano_t->Electron_vidNestedWPBitmap, nano_t->Electron_pt, 10.0);
      
    vector<int> ra2b_indices_e = filterLeptons(ra2b_t->Electrons_, ra2b_t->Electrons_fCoordinates_fPt, 10.0);
    vector<int> nano_indices_e = filterLeptons(nano_t->nElectron, nano_t->Electron_pt, 10.0);
    vector<int> ra2b_indices_m = filterLeptons(ra2b_t->Muons_, ra2b_t->Muons_fCoordinates_fPt, 10.0);
    vector<int> nano_indices_m = filterLeptons(nano_t->nMuon, nano_t->Muon_pt, 10.0);
    vector<int> ra2b_indices_p = filterLeptons(ra2b_t->Photons_, ra2b_t->Photons_fCoordinates_fPt, 30.0);
    vector<int> nano_indices_p = filterLeptons(nano_t->nPhoton, nano_t->Photon_pt, 30.0);
      cout <<"OK"<<endl;

    //cout << "num good jets :: ra2b " << ra2b_indices.size() << " nano " << nano_indices.size() << endl;

    for( int j= 0 ; j < 4 ; j++ ){
        //PHOTONS
        if(j<ra2b_indices_p.size() && j<ra2b_t->Photons_fullID->size() && j<ra2b_t->Photons_hasPixelSeed->size() && j<ra2b_t->Photons_passElectronVeto->size() && j<ra2b_t->Photons_isEB->size()){
            if(ra2b_t->Photons_fullID->at(ra2b_indices_p[j]) && !ra2b_t->Photons_hasPixelSeed->at(ra2b_indices_p[j]) && ra2b_t->Photons_passElectronVeto->at(ra2b_indices_p[j]) && /*ra2b_t->Photons_isEB->at(ra2b_indices_p[j]) &&*/ fabs(ra2b_t->Photons_fCoordinates_fEta[ra2b_indices_p[j]])<1){
                pho_pt_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fPt[ra2b_indices_p[j]]);
                pho_eta_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fEta[ra2b_indices_p[j]]);
                pho_phi_ra2b[j]->Fill(ra2b_t->Photons_fCoordinates_fPhi[ra2b_indices_p[j]]);
            }
        }
        if(j<nano_indices_p.size() /*&& j<nano_t->Photon_cutBased->size() && j<nano_t->Photon_pixelSeed->size() && j<nano_t->Photon_electronVeto->size()*/){
            if(nano_t->Photon_cutBased[j]>0 && !nano_t->Photon_pixelSeed[nano_indices_p[j]] && nano_t->Photon_electronVeto[nano_indices_p[j]] && /*nano_t->Photon_isScEtaEB[nano_indices_p[j]] &&*/ fabs(nano_t->Photon_eta[nano_indices_p[j]])<1){ //fail:0, loose:1, medium:2, tight:3
                pho_pt_nano[j]->Fill(nano_t->Photon_pt[nano_indices_p[j]]);
                pho_eta_nano[j]->Fill(nano_t->Photon_eta[nano_indices_p[j]]);
                pho_phi_nano[j]->Fill(nano_t->Photon_phi[nano_indices_p[j]]);
            }
        }
    }
      
  }

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetLogy();


  for( int j= 0 ; j < 4 ; j++ ){

      sprintf(temp,"Photon_pt%i.png",j);
      pho_pt_ra2b[j]->Draw();
      pho_pt_nano[j]->Draw("SAME");
      can->BuildLegend(0.4,0.9, 0.6, 0.8);
      can->SaveAs(temp);

      sprintf(temp,"Photon_eta%i.png",j);
      pho_eta_ra2b[j]->Draw();
      pho_eta_nano[j]->Draw("SAME");
      can->BuildLegend();
      can->SaveAs(temp);
        
      sprintf(temp,"Photon_phi%i.png",j);
      pho_phi_ra2b[j]->Draw();
      pho_phi_nano[j]->Draw("SAME");
      can->BuildLegend();
      can->SaveAs(temp);
  }
    
}
