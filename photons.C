#include "Nano.C"
#include "RA2b0.C"
#include "RA2b1.C"
#include "RA2b2.C"

bool debug = true;
int n=1;

vector<int> filterLeptons(UInt_t number, Float_t* pt, double pt_threshold/*, Float_t* eta, double eta_threshold*/){

    //int n=4;
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

  TFile* nano_file = new TFile("data/nano_sample.root");
  Nano* nano_t = new Nano((TTree*)nano_file->Get("Events"));
  TFile* ra2b_file0 = new TFile("data/10_RA2AnalysisTree.root");
  RA2b0* ra2b_t0 = new RA2b0((TTree*)ra2b_file0->Get("TreeMaker2/PreSelection"));
    TFile* ra2b_file1 = new TFile("data/263_RA2AnalysisTree.root");
    RA2b1* ra2b_t1 = new RA2b1((TTree*)ra2b_file1->Get("TreeMaker2/PreSelection"));
    TFile* ra2b_file2 = new TFile("data/282_RA2AnalysisTree.root");
    RA2b2* ra2b_t2 = new RA2b2((TTree*)ra2b_file2->Get("TreeMaker2/PreSelection"));

  char temp[100];
  
    vector<TH1F*> pho_pt_ra2b;
    vector<TH1F*> pho_pt_nano;
    for( int i = 0 ; i < n ; i++ ){
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
    for( int i = 0 ; i < n ; i++ ){
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
    for( int i = 0 ; i < n ; i++ ){
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

    
    
  int numEvents0 = ra2b_t0->fChain->GetEntriesFast();
    //cout << numEvents << endl;
  for( int evt0 = 0 ; evt0 < numEvents0 ; evt0++ ){
    ra2b_t0->GetEntry(evt0);
            
      
    vector<int> ind0 = filterLeptons(ra2b_t0->Electrons_, ra2b_t0->Electrons_fCoordinates_fPt, 30.0);
      int m = ind0.size();
    for( int j= 0 ; j < m ; j++ ){
        //PHOTONS
        if(j<ra2b_t0->Photons_fullID->size() && j<ra2b_t0->Photons_hasPixelSeed->size() && j<ra2b_t0->Photons_passElectronVeto->size() && j<ra2b_t0->Photons_isEB->size()){
            if(ra2b_t0->Photons_fullID->at(ind0[j]) && !ra2b_t0->Photons_hasPixelSeed->at(ind0[j]) && ra2b_t0->Photons_passElectronVeto->at(ind0[j]) /*&& ra2b_t0->Photons_isEB->at(ind0[j])*/&& fabs(ra2b_t0->Photons_fCoordinates_fEta[ind0[j]])<1){
                
                    pho_pt_ra2b[j]->Fill(ra2b_t0->Photons_fCoordinates_fPt[ind0[j]]);
                    pho_eta_ra2b[j]->Fill(ra2b_t0->Photons_fCoordinates_fEta[ind0[j]]);
                    pho_phi_ra2b[j]->Fill(ra2b_t0->Photons_fCoordinates_fPhi[ind0[j]]);
            }
        }
    }
      
  }
    
    

    int numEvents1 = ra2b_t1->fChain->GetEntriesFast();
      //cout << numEvents << endl;
    for( int evt1 = 0 ; evt1 < numEvents1 ; evt1++ ){
      ra2b_t1->GetEntry(evt1);
        
        
      vector<int> ind1 = filterLeptons(ra2b_t1->Electrons_, ra2b_t1->Electrons_fCoordinates_fPt, 30.0);
        int m = ind1.size();
      for( int j= 0 ; j < m ; j++ ){
          //PHOTONS
          if(j<ra2b_t1->Photons_fullID->size() && j<ra2b_t1->Photons_hasPixelSeed->size() && j<ra2b_t1->Photons_passElectronVeto->size() && j<ra2b_t1->Photons_isEB->size()){
          if(ra2b_t1->Photons_fullID->at(ind1[j]) && !ra2b_t1->Photons_hasPixelSeed->at(ind1[j]) && ra2b_t1->Photons_passElectronVeto->at(ind1[j]) /*&& ra2b_t1->Photons_isEB->at(ind1[j]) */&& fabs(ra2b_t1->Photons_fCoordinates_fEta[ind1[j]])<1){
                  pho_pt_ra2b[j]->Fill(ra2b_t1->Photons_fCoordinates_fPt[ind1[j]]);
                  pho_eta_ra2b[j]->Fill(ra2b_t1->Photons_fCoordinates_fEta[ind1[j]]);
                  pho_phi_ra2b[j]->Fill(ra2b_t1->Photons_fCoordinates_fPhi[ind1[j]]);
          }
          }
      }
        
    }
    
    
    int numEvents2 = ra2b_t2->fChain->GetEntriesFast();
      //cout << numEvents << endl;
    for( int evt2 = 0 ; evt2 < numEvents1 ; evt2++ ){
      ra2b_t2->GetEntry(evt2);
        
        
      vector<int> ind2 = filterLeptons(ra2b_t2->Electrons_, ra2b_t2->Electrons_fCoordinates_fPt, 30.0);
      int m = ind2.size();
      for( int j= 0 ; j < m ; j++ ){
          //PHOTONS
          if( j<ra2b_t2->Photons_fullID->size() && j<ra2b_t2->Photons_hasPixelSeed->size() && j<ra2b_t2->Photons_passElectronVeto->size() && j<ra2b_t2->Photons_isEB->size()){
          if(ra2b_t2->Photons_fullID->at(ind2[j]) && !ra2b_t2->Photons_hasPixelSeed->at(ind2[j]) && ra2b_t2->Photons_passElectronVeto->at(ind2[j]) /*&& ra2b_t2->Photons_isEB->at(ind2[j])*/ && fabs(ra2b_t2->Photons_fCoordinates_fEta[ind2[2]])<1){
                  pho_pt_ra2b[j]->Fill(ra2b_t2->Photons_fCoordinates_fPt[ind2[j]]);
                  pho_eta_ra2b[j]->Fill(ra2b_t2->Photons_fCoordinates_fEta[ind2[j]]);
                  pho_phi_ra2b[j]->Fill(ra2b_t2->Photons_fCoordinates_fPhi[ind2[j]]);
          }
          }
      }
        
    }
    
    int numEvents = nano_t->fChain->GetEntriesFast();
    int Kaka =numEvents0+numEvents1+numEvents2;
    cout << Kaka << "     " << numEvents << endl;
    for(int evt=0; evt <numEvents; evt++){
        nano_t->GetEntry(evt);
        
        vector<int> nano_indices_p = filterLeptons(nano_t->nElectron, nano_t->Electron_pt, 30.0);
        int m = nano_indices_p.size();
        for(int j=0; j <m; j++){
            //if(j<nano_indices_p.size() /*&& j<nano_t->Photon_cutBased->size() && j<nano_t->Photon_pixelSeed->size() && j<nano_t->Photon_electronVeto->size()*/){
            if(nano_t->Photon_cutBased[nano_indices_p[j]]>0 && !nano_t->Photon_pixelSeed[nano_indices_p[j]] && nano_t->Photon_electronVeto[nano_indices_p[j]] /*&& nano_t->Photon_isScEtaEB[nano_indices_p[j]] */&& fabs(nano_t->Photon_eta[nano_indices_p[j]])<1){ //fail:0, loose:1, medium:2, tight:3
                pho_pt_nano[j]->Fill(nano_t->Photon_pt[nano_indices_p[j]]);
                pho_eta_nano[j]->Fill(nano_t->Photon_eta[nano_indices_p[j]]);
                pho_phi_nano[j]->Fill(nano_t->Photon_phi[nano_indices_p[j]]);
            //}
            }
        }
    }
    

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetLogy();


  for( int j= 0 ; j < n ; j++ ){

      sprintf(temp,"Photon_pt%i.png",j);
      pho_pt_nano[j]->Draw();
      pho_pt_ra2b[j]->Draw("SAME");
      can->BuildLegend(0.4,0.9, 0.6, 0.8);
      can->SaveAs(temp);

      sprintf(temp,"Photon_eta%i.png",j);
      pho_eta_nano[j]->Draw();
      pho_eta_ra2b[j]->Draw("SAME");
      can->BuildLegend();
      can->SaveAs(temp);
        
      sprintf(temp,"Photon_phi%i.png",j);
      pho_phi_nano[j]->Draw();
      pho_phi_ra2b[j]->Draw("SAME");
      can->BuildLegend();
      can->SaveAs(temp);
  }
    
}
