#include "Nano.C"
#include "RA2b.C"
int n=1;

bool debug = false;

vector<int> filterLeptons(UInt_t number, Float_t* pt, double pt_threshold/*, Float_t* eta, double eta_threshold*/ ){

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




void photons(){

    gROOT->ProcessLine(".L ~/tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");

    TFile* nano_file = new TFile("data/nano_sample.root");
    Nano* nano_t = new Nano((TTree*)nano_file->Get("Events"));
    TFile* ra2b_file = new TFile("data/RA2bAnalysisTree.root");
    RA2b* ra2b_t = new RA2b((TTree*)ra2b_file->Get("TreeMaker2/PreSelection"));

    char temp[100];
  
    TH1F *pt_ra2b = new TH1F("TreeMaker Pt", ";Photon p_T [GeV];Events",80,0,800);
    pt_ra2b->SetLineWidth(2);
    pt_ra2b->SetLineStyle(1);
    pt_ra2b->SetLineColor(2);
    
    TH1F *pt_nano = new TH1F("Nano Pt", ";Photon p_T [GeV];Events",80,0,800);
    pt_nano->SetLineWidth(2);
    pt_nano->SetLineStyle(2);
    pt_nano->SetLineColor(4);

    TH1F* eta_ra2b = new TH1F("TreeMaker Eta",";Photon #eta [GeV];Events",50,-5,5);
    eta_ra2b->SetLineWidth(2);
    eta_ra2b->SetLineStyle(1);
    eta_ra2b->SetLineColor(2);
    
    TH1F* eta_nano = new TH1F("Nano Eta",";Photon #eta [GeV];Events",50,-5,5);
    eta_nano->SetLineWidth(2);
    eta_nano->SetLineStyle(2);
    eta_nano->SetLineColor(4);

    TH1F* phi_ra2b = new TH1F("TreeMaker Phi",";Photon #phi [GeV];Events",50,-5,5);
    phi_ra2b->SetLineWidth(2);
    phi_ra2b->SetLineStyle(1);
    phi_ra2b->SetLineColor(2);
    
    TH1F* phi_nano = new TH1F("Nano Phi",";Photon #phi [GeV];Events",50,-5,5);
    phi_nano->SetLineWidth(2);
    phi_nano->SetLineStyle(2);
    phi_nano->SetLineColor(4);

    int numEvents = ra2b_t->fChain->GetEntriesFast();
    //cout << numEvents << endl;
    for( int evt = 0 ; evt < numEvents ; evt++ ){
        if(debug) cout << "event: " << numEvents-evt-1 << endl;//evt << endl;
        ra2b_t->GetEntry(evt);
        nano_t->GetEntry(numEvents-evt-1);

        //vector<int> ra2b_indices_p = filterLeptons(ra2b_t->Photons_, ra2b_t->Photons_fCoordinates_fPt, 30.0, ra2b_t->Photons_fullID);
        //vector<int> nano_indices_p = filterLeptons(nano_t->nPhoton, nano_t->Photon_pt, 30.0);

        //cout << "num good jets :: ra2b " << ra2b_indices.size() << " nano " << nano_indices.size() << endl;

        for( int j= 0 ; j < ra2b_t->Photons_ ; j++ ){
            if(ra2b_t->Photons_fCoordinates_fPt[j]>30.0 && ra2b_t->Photons_fullID->at(j) && !ra2b_t->Photons_hasPixelSeed->at(j) &&     ra2b_t->Photons_passElectronVeto->at(j) && /*ra2b_t->Photons_isEB->at(ra2b_indices_p[j]) &&*/ fabs(ra2b_t->Photons_fCoordinates_fEta[j])<1){
                pt_ra2b->Fill(ra2b_t->Photons_fCoordinates_fPt[j]);
                eta_ra2b->Fill(ra2b_t->Photons_fCoordinates_fEta[j]);
                phi_ra2b->Fill(ra2b_t->Photons_fCoordinates_fPhi[j]);
            }
        }
        
        for (int j=0; j<nano_t->nPhoton;j++){
            if(nano_t->Photon_pt[j]>30.0 && nano_t->Photon_cutBased[j]>0 && !nano_t->Photon_pixelSeed[j] && nano_t->Photon_electronVeto[j] && /*nano_t->Photon_isScEtaEB[nano_indices_p[j]] &&*/ fabs(nano_t->Photon_eta[j])<1){ //fail:0, loose:1, medium:2, tight:3
                pt_nano->Fill(nano_t->Photon_pt[j]);
                eta_nano->Fill(nano_t->Photon_eta[j]);
                phi_nano->Fill(nano_t->Photon_phi[j]);
            }
        }
      
    }

    TCanvas* can = new TCanvas("can","can",500,500);
    can->SetLogy();

    pt_ra2b->Draw();
    pt_nano->Draw("SAME");
    can->BuildLegend();
    can->SaveAs("GammaPT.pdf");
    auto rp = new TRatioPlot(pt_ra2b,pt_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetLowerRefYaxis()->SetTitle("ratio ra2b/nano");
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Pt","TreeMaker Pt","l");
    legend->AddEntry("Nano Pt","Nano Pt","l");
    legend->Draw();
    cout << pt_nano->GetEntries() << endl;

    eta_ra2b->Draw();
    eta_nano->Draw("SAME");
    can->BuildLegend();
    can->SaveAs("GammaEta.pdf");
    auto rp = new TRatioPlot(eta_ra2b,eta_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetLowerRefYaxis()->SetTitle("ratio ra2b/nano");
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Eta","TreeMaker Eta","l");
    legend->AddEntry("Nano Eta","Nano Eta","l");
    legend->Draw();
    cout << eta_nano->GetEntries() << endl;
    
    phi_ra2b->Draw();
    phi_nano->Draw("SAME");
    can->BuildLegend();
    can->SaveAs("GammaPhi.pdf");
    auto rp = new TRatioPlot(phi_ra2b,phi_nano);
    can->SetTicks(0, 1);
    rp->Draw();
    rp->GetLowYaxis()->SetNdivisions(505);
    rp->GetLowerRefYaxis()->SetTitle("ratio ra2b/nano");
    rp->GetUpperPad()->cd();
    TLegend *legend = new TLegend(0.3,0.7,0.7,0.85);
    legend->AddEntry("TreeMaker Phi","TreeMaker Phi","l");
    legend->AddEntry("Nano Phi","Nano Phi","l");
    legend->Draw();
    cout << phi_nano->GetEntries() << endl;
    
    
}
