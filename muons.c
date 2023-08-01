#include "NanoTree.C"
#include "RA2bNtupleV20.C"

bool debug = false;

vector<int> filterLeptons(UInt_t number, Float_t* pt, double pt_threshold/*, Bool_t cutbasedLooseID, Bool_t softcutbasedID, Bool_t softmvaID, UChar_t highPtID, Float_t* eta, double eta_threshold*/){

    int n=1;
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

Bool_t vetoBinarymuon(Int_t bit){
    std::string binary = "";
    binary = decimalToBinary(bit);
        //if(binary.size()<30 || binary.substr(27, 3)=="000" || binary.substr(24, 3)=="000" || binary.substr(18, 3)=="000" || binary.substr(15, 3)=="000" || binary.substr(12, 3)=="000" || binary.substr(9, 3)=="000" || binary.substr(6, 3)=="000" || binary.substr(3, 3)=="000"){
    if(binary.size()<30 || binary.substr(12,3)=="000") return false;
        
    else return true;
        
}

vector<int> BitmapFilter(Int_t* bitmap, Float_t* pt, double pt_threshold){
    int n=4;
    vector<int> indices;
    for( int i = 0 ; i < n ; i++ ){
        //cout << bitmap[i] <<endl;
        if(pt[i] > pt_threshold && vetoBinarymuon(bitmap[i])/*&& fabs(eta[i]) < 2*/){
              //cout << "i: " << i << " pt: " << pt[i] << endl;
              indices.push_back(i);
        }
    }
    return indices;

}


void muons(){

    gROOT->ProcessLine(".L ~/tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");

    TFile* nano_file = new TFile("~/Downloads/Nano_Summer20UL18_TTJets_Inclusive_585C021C-8088-434F-A0A2-3BE09C1E5FD2.root");
    NanoTree* nano_t = new NanoTree((TTree*)nano_file->Get("Events"));
    TFile* ra2b_file = new TFile("~/Downloads/Summer20UL18_TTJets_Inclusive_10_278_RA2AnalysisTree.root");
    RA2bNtupleV20* ra2b_t = new RA2bNtupleV20((TTree*)ra2b_file->Get("TreeMaker2/PreSelection"));

    char temp[100];
    
    
  
    TH1F *pt_ra2b = new TH1F("TreeMaker Pt", ";Muon p_T [GeV];Events",80,0,800);
    pt_ra2b->SetLineWidth(2);
    pt_ra2b->SetLineStyle(1);
    pt_ra2b->SetLineColor(2);
    
    TH1F *pt_nano = new TH1F("Nano Pt", ";Muon p_T [GeV];Events",80,0,800);
    pt_nano->SetLineWidth(2);
    pt_nano->SetLineStyle(2);
    pt_nano->SetLineColor(4);

    TH1F* eta_ra2b = new TH1F("TreeMaker Eta",";Muon #eta [GeV];Events",50,-5,5);
    eta_ra2b->SetLineWidth(2);
    eta_ra2b->SetLineStyle(1);
    eta_ra2b->SetLineColor(2);
    
    TH1F* eta_nano = new TH1F("Nano Eta",";Muon #eta [GeV];Events",50,-5,5);
    eta_nano->SetLineWidth(2);
    eta_nano->SetLineStyle(2);
    eta_nano->SetLineColor(4);

    TH1F* phi_ra2b = new TH1F("TreeMaker Phi",";Muon #phi [GeV];Events",50,-5,5);
    phi_ra2b->SetLineWidth(2);
    phi_ra2b->SetLineStyle(1);
    phi_ra2b->SetLineColor(2);
    
    TH1F* phi_nano = new TH1F("Nano Phi",";Muon #phi [GeV];Events",50,-5,5);
    phi_nano->SetLineWidth(2);
    phi_nano->SetLineStyle(2);
    phi_nano->SetLineColor(4);



    int numEvents = ra2b_t->fChain->GetEntriesFast();
      //cout << numEvents << endl;
    for( int evt = 0 ; evt < numEvents ; evt++ ){
        if(debug) cout << "event: " << numEvents-evt-1 << endl;//evt << endl;
        ra2b_t->GetEntry(evt);
        nano_t->GetEntry(numEvents-evt-1);

        
        
        //vector<int> nano_indices_e = BitmapFilter(nano_t->Muon_vidNestedWPBitmap, nano_t->Muon_pt, 10.0);
        
        //vector<int> ra2b_indices_e = filterLeptons(ra2b_t->Muons_, ra2b_t->Muons_fCoordinates_fPt, 15.0);
        //vector<int> nano_indices_e = filterLeptons(nano_t->nMuon, nano_t->Muon_pt, 15.0);


        //cout << "num good jets :: ra2b " << ra2b_indices.size() << " nano " << nano_indices.size() << endl;

        for( int j= 0 ; j < ra2b_t->Muons_ ; j++ ){
                //bool iso = ra2b_t->Muons_passIso->at(j);
                //bool medium = ra2b_t->Muons_mediumID->at(j);
            if(/*iso &&*/ra2b_t->Muons_mediumID->at(j) && ra2b_t->Muons_fCoordinates_fPt[j]>15.0){//&& fabs(ra2b_t->Muons_fCoordinates_fEta[ra2b_indices_e[j]])<1){
                pt_ra2b->Fill(ra2b_t->Muons_fCoordinates_fPt[j]);
                eta_ra2b->Fill(ra2b_t->Muons_fCoordinates_fEta[j]);
                phi_ra2b->Fill(ra2b_t->Muons_fCoordinates_fPhi[j]);
            }
        }
            //Bool_t looseID=nano_t->Muon_looseId;
            //Bool_t softID=nano_t->Muon_softId[nano_indices_e[j]];
            //Bool_t softmvaID=nano_t->Muon_softMvaId;
            //UChar_t highptID=nano_t->Muon_highPtId;
            
        for(int j=0; j < nano_t->nMuon; j++){

            if (nano_t->Muon_mediumId[j] && nano_t->Muon_pt[j]>15.0/*&& fabs(nano_t->Muon_eta[nano_indices_e[j]])<1 && nano_t->Muon_dxy[nano_indices_e[j]]<0.2 && nano_t->Muon_dz[nano_indices_e[j]]<0.5*/){
                pt_nano->Fill(nano_t->Muon_pt[j]);
                eta_nano->Fill(nano_t->Muon_eta[j]);
                phi_nano->Fill(nano_t->Muon_phi[j]);
            }
        }
        
    }

    TCanvas* can = new TCanvas("can","can",500,500);
    can->SetLogy();

/*
    pt_nano->Draw();
    pt_ra2b->Draw("SAME");
    //can->BuildLegend(0.4,0.9, 0.6, 0.8);
    can->SaveAs(temp);
    auto rp = new TRatioPlot(pt_ra2b,pt_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Pt","TreeMaker Pt","l");
    legend->AddEntry("Nano Pt","Nano Pt","l");
    legend->Draw();

    
    eta_nano->Draw();
    eta_ra2b->Draw("SAME");
    can->BuildLegend(0.4,0.9, 0.6, 0.8);
    can->SaveAs(temp);
    auto rp = new TRatioPlot(eta_ra2b,eta_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Eta","TreeMaker Eta","l");
    legend->AddEntry("Nano Eta","Nano Eta","l");
    legend->Draw();
     
*/
    phi_nano->Draw();
    phi_ra2b->Draw("SAME");
    can->BuildLegend(0.4,0.9, 0.6, 0.8);
    can->SaveAs(temp);
    auto rp = new TRatioPlot(phi_ra2b,phi_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Phi","TreeMaker Phi","l");
    legend->AddEntry("Nano Phi","Nano Phi","l");
    legend->Draw();
    cout << phi_nano->GetEntries() << endl;
    
        
}
    

