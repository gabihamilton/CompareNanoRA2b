#include "NanoTree.C"
#include "RA2bNtupleV20.C"

bool debug = false;


//------------------------------------//
// BITWISE METHOD
int make_cut_bits(int nested_bitmap,int nr_cuts,int cut_size,int id_indx){
    int cut_bits = 0;
    int cut_mask = 0;
    for (int x=0; x<cut_size; x++){
        cut_mask |= 0x1 << x;
    }
                                                          
    for (int cut_nr = 0; cut_nr < nr_cuts; cut_nr++){
        //now we retrieve the cut of interest and get the pass code
        //0 = fail, >=1 veto, >=2 loose, >=3 medium, >=4 tight
        int cut_pass_code = (nested_bitmap >> cut_nr * cut_size) & cut_mask;
        if (cut_pass_code >= id_indx) {
            cut_bits |= 0x1 << cut_nr;
        }
    }
    return cut_bits;
}


//-------------------------------------------//
// GABIS METHOD FOR BITMAP
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
    if(binary.size()<30 || binary.substr(27, 3)=="000" || binary.substr(24, 3)=="000" || /* binary.substr(21, 3)=="000" || */binary.substr(18, 3)=="000" || binary.substr(15, 3)=="000" || binary.substr(12, 3)=="000" || binary.substr(9, 3)=="000" || binary.substr(6, 3)=="000" || binary.substr(3, 3)=="000") return false;
    //if(binary.size()<30 || binary.substr(12,3)=="000") return false;
        
    else return true;
        
}


vector<int> BitmapFilter(UInt_t number, Int_t* bitmap, Float_t* pt, double pt_threshold){
    vector<int> indices;
    //cout << number <<  endl;
    for( int i = 0 ; i < number ; i++ ){
        //cout << bitmap[i] <<endl;
        if(pt[i] > pt_threshold && vetoBinaryElectron(bitmap[i])/*&& fabs(eta[i]) < 2*/){
              //cout << "i: " << i << " pt: " << pt[i] << endl;
              indices.push_back(i);
        }
    }
    return indices;
}
//----------------------------------------//

void electrons(){


    gROOT->ProcessLine(".L ~/tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");

    TFile* nano_file = new TFile("~/Downloads/Nano_Summer20UL18_TTJets_Inclusive_585C021C-8088-434F-A0A2-3BE09C1E5FD2.root");
    NanoTree* nano_t = new NanoTree((TTree*)nano_file->Get("Events"));
    TFile* ra2b_file = new TFile("~/Downloads/Summer20UL18_TTJets_Inclusive_10_278_RA2AnalysisTree.root");
    RA2bNtupleV20* ra2b_t = new RA2bNtupleV20((TTree*)ra2b_file->Get("TreeMaker2/PreSelection"));

    char temp[100];
    
    TH1F *pt_ra2b = new TH1F("TreeMaker Pt", ";Electron p_T [GeV];Events",80,0,800);
    pt_ra2b->SetLineWidth(2);
    pt_ra2b->SetLineStyle(1);
    pt_ra2b->SetLineColor(2);
    
    TH1F *pt_nano = new TH1F("Nano Pt", ";Electron p_T [GeV];Events",80,0,800);
    pt_nano->SetLineWidth(2);
    pt_nano->SetLineStyle(2);
    pt_nano->SetLineColor(4);

    TH1F* eta_ra2b = new TH1F("TreeMaker Eta",";Electron #eta [GeV];Events",50,-5,5);
    eta_ra2b->SetLineWidth(2);
    eta_ra2b->SetLineStyle(1);
    eta_ra2b->SetLineColor(2);
    
    TH1F* eta_nano = new TH1F("Nano Eta",";Electron #eta [GeV];Events",50,-5,5);
    eta_nano->SetLineWidth(2);
    eta_nano->SetLineStyle(2);
    eta_nano->SetLineColor(4);

    TH1F* phi_ra2b = new TH1F("TreeMaker Phi",";Electron #phi [GeV];Events",50,-5,5);
    phi_ra2b->SetLineWidth(2);
    phi_ra2b->SetLineStyle(1);
    phi_ra2b->SetLineColor(2);
    
    TH1F* phi_nano = new TH1F("Nano Phi",";Electron #phi [GeV];Events",50,-5,5);
    phi_nano->SetLineWidth(2);
    phi_nano->SetLineStyle(2);
    phi_nano->SetLineColor(4);

    TH1F* iso_ra2b = new TH1F("TreeMaker iso",";Electron iso",50,0,10);
    iso_ra2b->SetLineWidth(2);
    iso_ra2b->SetLineStyle(1);
    iso_ra2b->SetLineColor(2);
    
    TH1F* iso_nano = new TH1F("Nano iso",";Electron iso",50,0,10);
    iso_nano->SetLineWidth(2);
    iso_nano->SetLineStyle(2);
    iso_nano->SetLineColor(4);

    int e_pt, e_eta, e_phi;
    int numEvents = ra2b_t->fChain->GetEntriesFast();
      cout << numEvents << endl;
    for( int evt = 0 ; evt < numEvents ; evt++ ){
        if(debug) cout << "event: " << numEvents-evt-1 << endl;//evt << endl;
        ra2b_t->GetEntry(evt);
        nano_t->GetEntry(numEvents-evt-1);

        for( int j= 0 ; j < ra2b_t->Electrons_ ; j++ ){

            if(ra2b_t->Electrons_fCoordinates_fPt[j]>10.0 /*&& ra2b_t->Electrons_mediumID->at(j) && ra2b_t->Electrons_passIso->at(j)*/){
                pt_ra2b->Fill(ra2b_t->Electrons_fCoordinates_fPt[j]);
                eta_ra2b->Fill(ra2b_t->Electrons_fCoordinates_fEta[j]);
                phi_ra2b->Fill(ra2b_t->Electrons_fCoordinates_fPhi[j]);
                iso_ra2b->Fill(ra2b_t->Electrons_iso->at(j));
                //cout << evt << " RA  " << ra2b_indices_e[j] << endl;
            }
            /*if(ra2b_t->Electrons_fCoordinates_fPt[j]>200 && ra2b_t->Electrons_fCoordinates_fPt[j]<220){
                cout << "RA2b  " << ra2b_t->EvtNum << endl;
                cout << "Pt  " << ra2b_t->Electrons_fCoordinates_fPt[j] << endl;
                cout << "Eta  " << ra2b_t->Electrons_fCoordinates_fEta[j] << endl;
                cout << "Phi  " << ra2b_t->Electrons_fCoordinates_fPhi[j] << endl;
                cout << "Charge  " << ra2b_t->Electrons_charge->at(j) << endl;
                cout << "Iso  " << ra2b_t->Electrons_iso->at(j) << endl;
                cout << "MediumID  " << ra2b_t->Electrons_mediumID->at(j) << endl;
                cout << "PassIso  " << ra2b_t->Electrons_passIso->at(j) << endl;
                cout << "tightID  " << ra2b_t->Electrons_tightID->at(j) << endl;
            }*/
        }
        
        for(int j=0; j < nano_t->nElectron; j++ ){
            int id_nr = 1; //cut based
            int nr_cuts = 10; //cut based has 9 cuts
            int cut_size = 3;// bit size per cut is 3 bits
            int cut_bits = make_cut_bits(nano_t->Electron_vidNestedWPBitmap[j],nr_cuts,cut_size,id_nr);
            //if((cut_bits & 0x3EF) == 0x3EF){
            //BITMAP
            if (nano_t->Electron_pt[j]/nano_t->Electron_eCorr[j]>10.0 /*&& nano_t->Electron_cutBased[j]>0*/ && nano_t->Electron_dxy[j]<0.1 && nano_t->Electron_dz[j]<0.2 && (cut_bits & 0x37F) == 0x37F /*&& nano_t->Electron_miniPFRelIso_all[j]<0.1*/){//except isolation: (cut_bits & 0x37F) == 0x37F){ //0:fail, 1:veto, 2:loose, 3:medium, 4:tight
                pt_nano->Fill(nano_t->Electron_pt[j]/nano_t->Electron_eCorr[j]);
                eta_nano->Fill(nano_t->Electron_eta[j]);
                phi_nano->Fill(nano_t->Electron_phi[j]);
                iso_nano->Fill(nano_t->Electron_miniPFRelIso_all[j]);//*nano_t->Electron_pt[j]/nano_t->Electron_eCorr[j]);
                //iso_nano->Fill(nano_t->Electron_pfRelIso03_all[j]*nano_t->Electron_pt[j]/nano_t->Electron_eCorr[j]);
                //cout << evt << " NANO  " << nano_indices_e[j] << endl;
            }
            
            //if(nano_t->Electron_pt[j]>200 && nano_t->Electron_pt[j]<220){
             /*if(nano_t->event==3112473 ||nano_t->event==31117312 || nano_t->event==32675621 || nano_t->event==32677578 || nano_t->event==719576 || nano_t->event==2764104 || nano_t->event==2768780 || nano_t->event==2104){
                cout << "Nano   " << nano_t->event << endl;
                cout << "Pt " << nano_t->Electron_pt[j] << endl;
                cout << "Eta    " << nano_t->Electron_eta[j] << endl;
                cout << "Phi    " << nano_t->Electron_phi[j] << endl;
                cout << "Charge " << nano_t->Electron_charge[j] << endl;
                cout << "Iso    " << nano_t->Electron_miniPFRelIso_all[j]*nano_t->Electron_pt[j] << endl;
                cout << "CutBased   " << nano_t->Electron_cutBased[j] << endl;
                cout << "PassIso    "  << endl;
                 cout << "  " <<endl;
            }*/

        }
    }


    TCanvas* can = new TCanvas("can","can",500,500);
    can->SetLogy();

/*
    pt_nano->Draw();
    pt_ra2b->Draw("SAME");
    can->BuildLegend(0.4,0.9, 0.6, 0.8);
    can->SaveAs("E_pt_final.pdf");
    //cout << e_pt_nano[j]->GetEntries() << endl;
    // Create and draw the ratio plot
    auto rp = new TRatioPlot(pt_ra2b,pt_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    //rp->GetLowerRefYaxis()->SetTitle("diff");
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Pt","TreeMaker Pt","l");
    legend->AddEntry("Nano Pt","Nano Pt","l");
    legend->Draw();

    eta_nano->Draw();
    eta_ra2b->Draw("SAME");
    can->BuildLegend(0.4,0.9, 0.6, 0.8);
    cout << eta_nano->GetEntries() << endl;
    // Create and draw the ratio plot
    auto rp = new TRatioPlot(eta_ra2b,eta_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("Nano Eta","Nano Eta","l");
    legend->AddEntry("TreeMaker Eta","TreeMaker Eta","l");
    legend->Draw();

    phi_nano->Draw();
    phi_ra2b->Draw("SAME");
    can->BuildLegend(0.4,0.9, 0.6, 0.8);
    cout << phi_nano->GetEntries() << endl;
    // Create and draw the ratio plot
    auto rp = new TRatioPlot(phi_ra2b,phi_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetUpperPad()->cd();
    //rp->GetLowerRefYaxis()->SetTitle("diff");
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("Nano Phi","Nano Phi","l");
    legend->AddEntry("TreeMaker Phi","TreeMaker Phi","l");
    legend->Draw();
 
 */
    iso_ra2b->Draw();
    iso_nano->Draw("SAME");
    can->BuildLegend(0.4,0.9, 0.6, 0.8);
    cout << phi_nano->GetEntries() << endl;
    // Create and draw the ratio plot
    auto rp = new TRatioPlot(iso_nano,iso_ra2b);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetUpperPad()->cd();
    //rp->GetLowerRefYaxis()->SetTitle("diff");
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("Nano iso","Nano iso","l");
    legend->AddEntry("TreeMaker iso","TreeMaker iso","l");
    legend->Draw();
    
   
}
    

