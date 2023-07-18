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
    
    
  
    vector<TH1F*> e_pt_ra2b;
    vector<TH1F*> e_pt_nano;
    for( int i = 0 ; i < 4 ; i++ ){
        //sprintf(temp,"muonpt_ra2b%i",i);
        sprintf(temp, "RA2b");
        e_pt_ra2b.push_back(new TH1F("RA2b",";muon p_T [GeV];Events",80,0,800));
        e_pt_ra2b.back()->SetLineWidth(2);
        e_pt_ra2b.back()->SetLineStyle(1);
        e_pt_ra2b.back()->SetLineColor(2);
        //sprintf(temp,"muonpt_nano%i",i);
        sprintf(temp, "Nano");
        e_pt_nano.push_back(new TH1F("Nano",";muon p_T [GeV];Events",80,0,800));
        e_pt_nano.back()->SetLineWidth(2);
        e_pt_nano.back()->SetLineStyle(2);
        e_pt_nano.back()->SetLineColor(4);
    }

    vector<TH1F*> e_eta_ra2b;
    vector<TH1F*> e_eta_nano;
    for( int i = 0 ; i < 4 ; i++ ){
        //sprintf(temp,"muoneta_ra2b%i",i);
        sprintf(temp, "RA2b");
        e_eta_ra2b.push_back(new TH1F("RA2b",";muon #eta [GeV];Events",50,-5,5));
        e_eta_ra2b.back()->SetLineWidth(2);
        e_eta_ra2b.back()->SetLineStyle(1);
        e_eta_ra2b.back()->SetLineColor(2);
        //sprintf(temp,"muoneta_nano%i",i);
        sprintf(temp, "Nano");
        e_eta_nano.push_back(new TH1F("Nano",";muon #eta [GeV];Events",50,-5,5));
        e_eta_nano.back()->SetLineWidth(2);
        e_eta_nano.back()->SetLineStyle(2);
        e_eta_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> e_phi_ra2b;
    vector<TH1F*> e_phi_nano;
    for( int i = 0 ; i < 4 ; i++ ){
        //sprintf(temp,"muonphi_ra2b%i",i);
        sprintf(temp, "RA2b");
        e_phi_ra2b.push_back(new TH1F("RA2b",";muon #phi [GeV];Events",50,-5,5));
        e_phi_ra2b.back()->SetLineWidth(2);
        e_phi_ra2b.back()->SetLineStyle(1);
        e_phi_ra2b.back()->SetLineColor(2);
        //sprintf(temp,"muonphi_nano%i",i);
        sprintf(temp, "Nano");
        e_phi_nano.push_back(new TH1F("Nano",";muon #phi [GeV];Events",50,-5,5));
        e_phi_nano.back()->SetLineWidth(2);
        e_phi_nano.back()->SetLineStyle(2);
        e_phi_nano.back()->SetLineColor(4);
    }
  
    vector<TH1F*> e_iso_ra2b;
    vector<TH1F*> e_iso_nano;
    for( int i = 0 ; i < 4 ; i++ ){
        sprintf(temp,"muon_iso_ra2b%i",i);
        e_iso_ra2b.push_back(new TH1F(temp,";muon iso [GeV];Events",50,0,50));
        e_iso_ra2b.back()->SetLineWidth(2);
        e_iso_ra2b.back()->SetLineStyle(1);
        e_iso_ra2b.back()->SetLineColor(2);
        sprintf(temp,"muon_iso_nano%i",i);
        e_iso_nano.push_back(new TH1F(temp,";muon iso [GeV];Events",50,0,50));
        e_iso_nano.back()->SetLineWidth(2);
        e_iso_nano.back()->SetLineStyle(2);
        e_iso_nano.back()->SetLineColor(4);
    }
    
    vector<TH1F*> sieie_ra2b;
    vector<TH1F*> sieie_nano;
    for( int i = 0 ; i < 4 ; i++ ){
        sprintf(temp,"Sieie_ra2b%i",i);
        sieie_ra2b.push_back(new TH1F(temp,";muon #phi [GeV];Events",50,0,1));
        sieie_ra2b.back()->SetLineWidth(2);
        sieie_ra2b.back()->SetLineStyle(1);
        sieie_ra2b.back()->SetLineColor(2);
        sprintf(temp,"Sieie_nano%i",i);
        sieie_nano.push_back(new TH1F(temp,";muon #phi [GeV];Events",50,0,0.015));
        sieie_nano.back()->SetLineWidth(2);
        sieie_nano.back()->SetLineStyle(2);
        sieie_nano.back()->SetLineColor(4);
    }



    int numEvents = ra2b_t->fChain->GetEntriesFast();
      //cout << numEvents << endl;
    for( int evt = 0 ; evt < numEvents ; evt++ ){
        if(debug) cout << "event: " << numEvents-evt-1 << endl;//evt << endl;
        ra2b_t->GetEntry(evt);
        nano_t->GetEntry(numEvents-evt-1);

        
        
        //vector<int> nano_indices_e = BitmapFilter(nano_t->Muon_vidNestedWPBitmap, nano_t->Muon_pt, 10.0);
        
        vector<int> ra2b_indices_e = filterLeptons(ra2b_t->Muons_, ra2b_t->Muons_fCoordinates_fPt, 15.0);
        vector<int> nano_indices_e = filterLeptons(nano_t->nMuon, nano_t->Muon_pt, 15.0);


        //cout << "num good jets :: ra2b " << ra2b_indices.size() << " nano " << nano_indices.size() << endl;

        for( int j= 0 ; j < 1 ; j++ ){
            if( j < ra2b_indices_e.size() /*&& j<ra2b_t->Muons_passIso->size()*/ && j<ra2b_t->Muons_mediumID->size()){
                //bool iso = ra2b_t->Muons_passIso->at(j);
                //bool medium = ra2b_t->Muons_mediumID->at(j);
                if(/*iso &&*/ra2b_t->Muons_mediumID->at(j)){//&& fabs(ra2b_t->Muons_fCoordinates_fEta[ra2b_indices_e[j]])<1){
                    e_pt_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fPt[ra2b_indices_e[j]]);
                    e_eta_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fEta[ra2b_indices_e[j]]);
                    e_phi_ra2b[j]->Fill(ra2b_t->Muons_fCoordinates_fPhi[ra2b_indices_e[j]]);
                    //e_iso_ra2b[j]->Fill(ra2b_t->Muons_iso->at(ra2b_indices_e[j]));
                }
            }
            //Bool_t looseID=nano_t->Muon_looseId;
            //Bool_t softID=nano_t->Muon_softId[nano_indices_e[j]];
            //Bool_t softmvaID=nano_t->Muon_softMvaId;
            //UChar_t highptID=nano_t->Muon_highPtId;
            

            if( j < nano_indices_e.size() /*&& nano_t->Muon_softMvaId[nano_indices_e[j]] && !softmvaID && highptID!=1 && highptID!=2*/){
                if (nano_t->Muon_mediumId[nano_indices_e[j]] /*&& fabs(nano_t->Muon_eta[nano_indices_e[j]])<1 && nano_t->Muon_dxy[nano_indices_e[j]]<0.2 && nano_t->Muon_dz[nano_indices_e[j]]<0.5*/){
                    e_pt_nano[j]->Fill(nano_t->Muon_pt[nano_indices_e[j]]);
                    e_eta_nano[j]->Fill(nano_t->Muon_eta[nano_indices_e[j]]);
                    e_phi_nano[j]->Fill(nano_t->Muon_phi[nano_indices_e[j]]);
                    //e_iso_nano[j]->Fill(nano_t->Muon_miniPFRelIso_all[nano_indices_e[j]]);
                    //sieie_nano[j]->Fill(nano_t->Muon_sieie[nano_indices_e[j]]);
                }
            }
          
        }
    }

    TCanvas* can = new TCanvas("can","can",500,500);
    can->SetLogy();


    for( int j= 0 ; j < 1 ; j++ ){
 /*       sprintf(temp,"muon_pt%i.png",j);
        e_pt_nano[j]->Draw();
        e_pt_ra2b[j]->Draw("SAME");
        //can->BuildLegend(0.4,0.9, 0.6, 0.8);
        can->SaveAs(temp);
        auto rp = new TRatioPlot(e_pt_ra2b[j],e_pt_nano[j],  "diff");
        can->SetTicks(0, 1);
        rp->Draw();
        rp->GetLowYaxis()->SetNdivisions(505);
        rp->GetUpperPad()->cd();
        TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
        legend->AddEntry("RA2b","RA2b","l");
        legend->AddEntry("Nano","Nano","l");
        legend->Draw();

        sprintf(temp,"muon_eta%i.png",j);
        e_eta_nano[j]->Draw();
        e_eta_ra2b[j]->Draw("SAME");
        can->BuildLegend(0.4,0.9, 0.6, 0.8);
        can->SaveAs(temp);
         auto rp = new TRatioPlot(e_eta_ra2b[j],e_eta_nano[j],  "diff");
         can->SetTicks(0, 1);
         rp->Draw();
         rp->GetLowYaxis()->SetNdivisions(505);
         rp->GetUpperPad()->cd();
         TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
         legend->AddEntry("RA2b","RA2b","l");
         legend->AddEntry("Nano","Nano","l");
         legend->Draw();
         
*/
        sprintf(temp,"muon_phi%i.png",j);
        e_phi_nano[j]->Draw();
        e_phi_ra2b[j]->Draw("SAME");
        can->BuildLegend(0.4,0.9, 0.6, 0.8);
        can->SaveAs(temp);
        auto rp = new TRatioPlot(e_phi_ra2b[j],e_phi_nano[j],  "diff");
        can->SetTicks(0, 1);
        rp->Draw();
        rp->GetLowYaxis()->SetNdivisions(505);
        rp->GetUpperPad()->cd();
        TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
        legend->AddEntry("RA2b","RA2b","l");
        legend->AddEntry("Nano","Nano","l");
        legend->Draw();
        cout << e_phi_nano[j]->GetEntries() << endl;
        
        /*
        sprintf(temp,"muon_iso%i.png",j);
        e_iso_ra2b[j]->Draw();
        e_iso_nano[j]->Draw("SAME");
        can->BuildLegend(0.4,0.9, 0.6, 0.8);
        can->SaveAs(temp);
        
        sprintf(temp,"Sieie%i.png",j);
        //e_iso_ra2b[j]->Draw();
        sieie_nano[j]->Draw();
        can->BuildLegend(0.4,0.9, 0.6, 0.8);
        can->SaveAs(temp);*/
    }
        
}
    

