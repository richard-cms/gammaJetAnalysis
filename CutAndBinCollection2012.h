#ifndef CutAndBinCollection_C
#define CutAndBinCollection_C
double a1, a2, a3, a4, a5, a6;


#include <TF1.h>
#include <TCut.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <math.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "commonUtility.h"
#include "multiTreeUtilPhoton2011.h"
#include "histFunctionD.C"

#define PI 3.141592653589


///////////// pp Data
TString fnamePPDATA                  = "yskimmedFiles/skim_ak3PF_ppData2013_promptSkim_photon40GeV.root";
// pp MC
TString fnamePPMC_AllQcdPho30to50    = "yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root";
TString fnamePPMC_AllQcdPho50to80    = "yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root";
TString fnamePPMC_AllQcdPho80to120   = "yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root";
TString fnamePPMC_AllQcdPho120to9999 = "yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root";
double  wPPMC_AllQcdPho30to50        = 29329./ 29329.;
double  wPPMC_AllQcdPho50to80        = 8098. / 87988.;
double  wPPMC_AllQcdPho80to120       = 1680. / 96756.;
double  wPPMC_AllQcdPho120to9999     = 438.  / 90972.;


///////////// pA Data
TString fnamePADATA                  = "yskimmedFiles/yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root";
//            pA MC 
TString fnamePAMC_AllQcdPho30to50    = "yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85.root";
TString fnamePAMC_AllQcdPho50to80    = "yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85.root";
TString fnamePAMC_AllQcdPho80to120   = "yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85.root";
TString fnamePAMC_AllQcdPho120to9999 = "yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85.root";
double  wPAMC_AllQcdPho30to50        = 56669./ 50385.;
double  wPAMC_AllQcdPho50to80        = 41906./ 114136.;
double  wPAMC_AllQcdPho80to120       = 12044./ 103562.;
double  wPAMC_AllQcdPho120to9999     = 4481. / 151511.;



///////////// PbPb Data
TString fnameHIDATA                  = "yskimmedFiles/yskim_HiForestPhoton-v7-noDuplicate.root";
// PbPb MC
TString fnameHIMC_AllQcdPho30to50    =  "yskimmedFiles/yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root";
TString fnameHIMC_AllQcdPho50to80    =  "yskimmedFiles/yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root";
TString fnameHIMC_AllQcdPho80to9999  =  "yskimmedFiles/yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root";
double  wHIMC_AllQcdPho30to50        = 32796./ 32796.;
double  wHIMC_AllQcdPho50to80        = 21470./ 53876.;
double  wHIMC_AllQcdPho80to9999       = 6462. / 58781.;

const float awayRange= PI * 7./8.;


// DON'T FORGET TO APPLY HOE CUT SEPARATELY    
// Convinient Output Classes                                                                                                                 

// sample typle
enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
TString getSampleName ( sampleType colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
}
TString getSampleName ( int colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
}

const int nMixing1 = 20;

const int kHIMCNoJetWeight = 2001;

struct valPair {
  double val;
  double err;
};

struct jetKinem {
  double  pt;
  double  eta;
  double  phi;
  int  subid;  // gen Matched subid;
};

struct jetMatchVar{
  double  theJetPt;
  double  theJetEta;
  double  theJetPhi;
  int  theJetSubid;  // gen Matched subid;
  double theJetCR;

};





class Isolation{
 public:
  float cc1,cc2,cc3,cc4,cc5;
  float cr1,cr2,cr3,cr4,cr5;
  float ct1PtCut20,ct2PtCut20,ct3PtCut20,ct4PtCut20,ct5PtCut20;
  float ecalIso,hcalIso,trackIso;
  
  void Set(HiForest * c, int j) {    cc1=c->photon.cc1[j];
    cc2=c->photon.cc2[j];
    cc3=c->photon.cc3[j];
    cc4=c->photon.cc4[j];
    cc5=c->photon.cc5[j];
    cr1=c->photon.cr1[j];
    cr2=c->photon.cr2[j];
    cr3=c->photon.cr3[j];
    cr4=c->photon.cr4[j];
    cr5=c->photon.cr5[j];
    ct1PtCut20=c->photon.ct1PtCut20[j];
    ct2PtCut20=c->photon.ct2PtCut20[j];
    ct3PtCut20=c->photon.ct3PtCut20[j];
    ct4PtCut20=c->photon.ct4PtCut20[j];
    ct5PtCut20=c->photon.ct5PtCut20[j];
    ecalIso = c->photon.ecalRecHitSumEtConeDR04[j];
    hcalIso = c->photon.hcalTowerSumEtConeDR04[j];
    trackIso = c->photon.trkSumPtHollowConeDR04[j];
  }
};



class GammaJet {
 public:
 GammaJet() :
  photonEt(-99),photonRawEt(-99),
    photonEta(9999),photonPhi(9999),
    hovere(10000),
    r9(10000),
    sigmaIetaIeta(-99),
    sumIsol(99999),
    genIso(99999),
    genPhotonEt(-99),
    genMomId(-999999),
    lJetPt(-999990),
    lJetEta(-999990),
    lJetPhi(-999990),
   lJetDphi(-999990),
   lJetSubid(-999990)

      {}
  float photonEt,photonRawEt;
  float photonEta;
  float photonPhi;
  float hovere,r9, sigmaIetaIeta, sumIsol;
    float genIso;
    float genPhotonEt;
    int genMomId;
    float lJetPt;
    float lJetEta;
    float lJetPhi;
    float lJetDphi;
    int lJetSubid;
    void clear() {
      photonRawEt=-99; photonEt = -99999; photonEta=100; photonPhi=1000;
      sigmaIetaIeta=-99;
      sumIsol = -99;
      genIso = 9990;
      genPhotonEt = -99;
      genMomId = -999999;
      hovere  =  1000;
      r9      =  1000;
      lJetPt = -99999;
      lJetEta = -99999;
      lJetPhi = -99999;
      lJetDphi = -99999;
      lJetSubid= -99999;
    }
};

class DiJet {
 public:
  DiJet() :
    pthat(-99),
    lJetPt(-99), slJetPt(-99),
    lJetRawPt(-99), slJetRawPt(-99),
    lJetEta(-99), slJetEta(-99),
    lJetPhi(-99), slJetPhi(-99),
    lJetPtGM(-99), slJetPtGM(-99),
    lJetEtaGM(-99), slJetEtaGM(-99),
    lJetPhiGM(-99), slJetPhiGM(-99),
    lJetChgSum(-99), slJetChgSum(-99),
    lJetPhoSum(-99), slJetPhoSum(-99),
    lJetNtrSum(-99), slJetNtrSum(-99),
    lJetRecoEoH(-99), slJetRecoEoH(-99),
    lJetGenEoH(-99), slJetGenEoH(-99),
    lJetFlav(-99),    slJetFlav(-99)
    

    {}
    float pthat;
    float lJetPt, slJetPt;
    float lJetRawPt, slJetRawPt;
    float lJetEta, slJetEta;
    float lJetPhi, slJetPhi;
    float lJetPtGM, slJetPtGM;
    float lJetEtaGM, slJetEtaGM;
    float lJetPhiGM, slJetPhiGM;
    float lJetChgSum,   slJetChgSum;
    float lJetPhoSum,   slJetPhoSum;
    float lJetNtrSum,   slJetNtrSum;
    float lJetRecoEoH, slJetRecoEoH;
    float lJetGenEoH, slJetGenEoH;
    float lJetFlav,    slJetFlav;
      


    void clear() {
    pthat=-99;
    lJetPt = -99; slJetPt = -99;
    lJetRawPt = -99; slJetRawPt = -99;
    lJetEta = -99; slJetEta = -99;
    lJetPhi = -99; slJetPhi = -99;
    lJetPtGM = -99; slJetPtGM = -99;
    lJetEtaGM = -99; slJetEtaGM = -99;
    lJetPhiGM = -99; slJetPhiGM = -99;
    lJetChgSum = -99; slJetChgSum = -99; 
    lJetPhoSum = -99; slJetPhoSum = -99;
    lJetNtrSum = -99; slJetNtrSum = -99;
    lJetRecoEoH = -99; slJetRecoEoH = -99;
    lJetGenEoH = -99; slJetGenEoH = -99;
    lJetFlav      = -99; slJetFlav = -99;  
    
    }
};



class EvtSel {
 public:
 EvtSel() :
  run(0),   evt(0),    cBin(0),  pBin(0), 
    trig(0),  offlSel(0),
    noiseFilt(0),  anaEvtSel(0),  vz(0),  reweight(0),
    hf4Pos(-1), hf4Neg(-1), hf4Sum(-1) 
    {}
  
  int run;
  int evt;
  int cBin;
  int pBin;
  bool trig;
  bool offlSel;
  bool noiseFilt;
  bool anaEvtSel;
  float vz;
  float reweight;
  float hf4Pos;
  float hf4Neg;
  float hf4Sum;

  
  void clear() {
    run = -99999;   evt = -99999;    cBin = -99999;  pBin = -99999;
    trig = -99999;  offlSel = -99999;
    noiseFilt = -99999;  anaEvtSel = -99999;  vz = -99999;  reweight = -99999;
    hf4Pos = -1;  hf4Neg = -1 ; hf4Sum = -1 ;
  }
  
  
};


class fitResult {
 public:
  double nSig;
  double nSigErr;
  double purity010;
  double chisq;
};





TCut isoSumCut  = "(cc4+cr4+ct4PtCut20)/0.9 <1";

TCut sbIsoCut =" (cc4+cr4+ct4PtCut20)/0.9>10 && (cc4+cr4+ct4PtCut20)/0.9 < 20 ";
TCut sbIsoPPCut = sbIsoCut;


float isolationCut = 5.0;

TCut isFragment = "abs(genMomId)<22";
TCut isPrompt = "abs(genMomId)==22";

TCut genMatchCut0      = "isGenMatched && abs(genMomId)<=22";
TCut genMatchCut1      = Form("isGenMatched && genMomId==22 && genCalIsoDR04 < %.1f",isolationCut);
TCut genMatchCut      = Form("(isGenMatched && abs(genMatchedEta)<1.44 && abs(etCorrected/genMatchedPt-1)<.3 && abs(genMomId) <= 22 && genCalIsoDR04 < %.1f)",isolationCut);
TCut genMatchCutBkg      = "(isGenMatched && abs(genMatchedEta)<1.44 && abs(etCorrected/genMatchedPt-1)<.6)  &&  ( (abs(genMomId) > 22) || (genCalIsoDR04 > 5.0) ) ";


TCut genPhotonCut     = Form("( abs(gpEta) < 1.44 && abs(gpId)==22 && abs(gpMomId) <= 22 && gpCollId ==0  && gpIsoDR04 < %.3f)",isolationCut);



TString swissCrx      = "(1 - (eRight+eLeft+eTop+eBottom)/eMax)";
TCut hiSpikeCutMC     = Form("(  %s < 0.90 && sigmaIetaIeta>0.002 && sigmaIphiIphi>0.002)",swissCrx.Data());
TCut ppSpikeCutMC     = Form("(  %s < 0.95 && sigmaIetaIeta>0.002 && sigmaIphiIphi>0.002)",swissCrx.Data());

//TCut hiSpikeCutNoPhi  = Form("( ( %s < 0.90 && sigmaIetaIeta>0.002) ",swissCrx.Data());      

//TCut hiSpikeCutNoPhi  = Form("( ( %s < 0.90 && sigmaIetaIeta>0.002) ",swissCrx.Data());


TCut seedTimeCut      = "abs(seedTime)<3";
TCut hiSpikeCutData   = hiSpikeCutMC && seedTimeCut;
TCut ppSpikeCutData   = ppSpikeCutMC && seedTimeCut;

TCut etaCut       = "abs(eta)<1.44 && abs(scEta)<1.479";

//TCut etaCut           = " (abs(scEta) < 1.479 && abs(eta)<1.44) && (rawEnergy/energy > 0.5)";// && (!isEBGap&&!isEEGap&&!isEBEEGap)";

TCut genEtaCut  =       "(abs(eta) < 1.44)";
TCut finalCutSigHI  = genMatchCut     &&  hiSpikeCutMC && etaCut ;
TCut finalCutBkgHI  = !genMatchCut  &&  hiSpikeCutMC && etaCut ;
TCut finalCutDataHI =                   hiSpikeCutData && etaCut;

TCut finalCutSigPP  = genMatchCut     &&  ppSpikeCutMC && etaCut;
TCut finalCutBkgPP  = !genMatchCut  &&  ppSpikeCutMC && etaCut;
TCut finalCutDataPP =                     ppSpikeCutData && etaCut;



TCut finalCutGen  =  genPhotonCut ;




// Cuts for track and jets
double cutjetPtSkim = 20;
double cuttrkEtaSkim = 2.0;

double cutjetEta = 1.6;
double cutjetEtaSkim = 3.0;

double cuttrkPt =  10;
double cuttrkEta  = 2.0;
double drCutTJ = 0.3 ;  // cut for tracks in jets    


int ycolor[9] =  {0,1,2,4,8,20,1,1,1};  // the for centrality bins...
int ycolorEt[9]= {0,1,2,4,8,20,1,1,1};

// temporar.y!!!

const int theEvtPlNumber = 21;


int nCentBinSkim = 40;
int nCentBinSkimPA = 10;
int getHfBin( float hf4Sum=-1 ) { 
  if ( hf4Sum < -1 )   return -1;
  else if ( hf4Sum < 5 )   return 0;
  else if ( hf4Sum < 10)   return 1;
  else if ( hf4Sum < 15)   return 2;
  else if ( hf4Sum < 20 )   return 3;
  else if ( hf4Sum < 25 )   return 4;
  else if ( hf4Sum < 30 )   return 5;
  else if ( hf4Sum < 35 )   return 6;
  else if ( hf4Sum < 40 )   return 7;
  else if ( hf4Sum < 45 )   return 8;
  else                      return 9;
}



const int nCentBin1 = 4;
double centBin1[nCentBin1+1] = {0,4,12,20,40};


const int nCentBinPa = 1;
//double centBinPa[nCentBinPa+1] = {0,20,30,100};
double centBinPa[nCentBinPa+1] = {0,100};
//double centBinPa[nCentBinPa+1] = {0,20,25,30,40,100};

const int nPtBinPa = 4; 
double ptBinPa[nPtBinPa+1]    = {40,50,60,80,9999}; 
double ptBinPaDraw[nPtBinPa+1]    = {45,55,70,100,200};


float vtxCutPhotonAna = 15;
float jetDPhiCut = PI * 7./8.;

const int nVtxBin =1;
const int nPlnBin = 1;






void mcStyle(TH1* h=0) {
   h->SetLineColor(kPink);
   h->SetFillColor(kOrange+7);
   h->SetFillStyle(3004);
}

void sbStyle(TH1* h=0) {
   h->SetLineColor(kGreen+4);
   h->SetFillColor(kGreen+1);
   h->SetFillStyle(3001);
}

void dijetStyle(TH1* h=0) {
   h->SetLineColor(kBlue);
   h->SetFillColor(kAzure-8);
   h->SetFillStyle(3001);
}

double getNoEmc (TString theFname="", TCut theCut="") {
   TFile *fd = new TFile(theFname.Data());
   TTree *ana = (TTree*) fd->FindObjectAny("Analysis");
   cout << "number of events of " << theCut.GetTitle() << "    : " << ana->GetEntries( theCut ) << endl;
   return ana->GetEntries( theCut ) ;
}




void setupMTU(multiTreeUtil* photon1=0 , sampleType collision = kHIDATA){  // obsolete subroutine
  if ( collision == kHIDATA) 
    photon1->addFile(fnameHIDATA, "tgj","",1);
  else if ( collision == kPPDATA)
    photon1->addFile(fnamePPDATA, "tgj","",1);
  
  photon1->AddFriend("yTrk=yTrack");
  photon1->AddFriend("yJet");
  photon1->AddFriend("mJet");
  
  //  photon1->AddFriend("mTrk1");
  //  photon1->AddFriend("mTrk2");
  
  if (collision == kHIMC)  {
    photon1->AddFriend("gp");
    photon1->AddFriend("mGp1");
    photon1->AddFriend("mGp2");
  }
}

void setupMTU_Pho(multiTreeUtil* photon1=0 , bool isMC=false) {
  
  photon1->AddFriend("yTrk=yTrack");
  photon1->AddFriend("mTrk");
  photon1->AddFriend("yPhoton=yongsunPhotonTree");
  photon1->AddFriend("yJet");
  if ( isMC){
    photon1->AddFriend("gp");
    photon1->AddFriend("mGp");
  }
}








class CutAndBinCollection
{
 public:
   CutAndBinCollection() {
   }
   ~CutAndBinCollection() {
      
   }
   //   float getHoECut( float percentBin=1, float et=30 ); 
   TString getTmplName()  { return tmplName_;};
   TString getTmplVar()   { return tmplVar_;};
   TString getTmplVarMC() { return tmplVarMC_;};
   TString getTmplVarBkg() { return tmplVarBkg_;};
  
   TString getTmplLeg()   { return tmplLeg_;};
   TString getTmplXTitle(){ return tmplXTitle_;};
  
   int  getNTmplBin() {     return nTmplBin_;};
   float getTmplMin() {     return tmplMin_;};
   float getTmplMax() {     return tmplMax_;};
   float getConeSize(){     return coneSize_;};
   float getFitMin()  {     return fitMin_;};
   float getFitMax()  {     return fitMax_;};
   
   bool isHI()      {       return hiOrPp_;};

   
   int getNPtBin() { return ptBin_.size()-1;};
   int getNJetPtBin() { return jetPtBin_.size()-1;};
   int getNPtBinAssoc() { return ptBinAssoc_.size()-1;};
   int getNCentBin() { return centBin_.size()-1;};
   
   vector<double> getPtBin() { return ptBin_;};
   vector<double> getCentBin() { return centBin_;};
   vector<double> getPtBinAssoc() { return ptBinAssoc_;};
   vector<double> getJetPtBin() { return jetPtBin_;};
   TString getPurityFileName() { return purityFname_;};
   void setCuts(int cutOpt);
 private:
   
   TString tmplName_;
   TString tmplVar_;
   TString tmplVarMC_;
   TString tmplVarBkg_;
   
   TString tmplLeg_;
   TString tmplXTitle_;
   TCut IBCutWOEleVeto_;
   TCut IBCut_;
   TCut SBCut_;
   int nTmplBin_;
   float tmplMin_;
   float tmplMax_;
   float fitMin_;
   float fitMax_;
   bool hiOrPp_;
   float coneSize_;
   

   vector<double> ptBin_;
   vector<double> ptBinAssoc_; // tracks
   vector<double> centBin_;
   vector<double> jetPtBin_;   // jet pt
   
   TString purityFname_;
   float jetPTCut_;
   
};

void CutAndBinCollection::setCuts( int cutOpt ) { 
  purityFname_ = Form("photonPurityCollection2012_cutOption%d.root",cutOpt);
  centBin_.clear();
  ptBin_.clear();
  ptBinAssoc_.clear();
  jetPtBin_.clear();


  if ( cutOpt == 602003) {
    coneSize_ = 0.3;

    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);
    
    ptBin_.push_back(60);
    ptBin_.push_back(1000);
    
    jetPtBin_.push_back(20);
    jetPtBin_.push_back(30);
    jetPtBin_.push_back(40);
    jetPtBin_.push_back(50);
    jetPtBin_.push_back(60);
    jetPtBin_.push_back(1000);

    ptBinAssoc_.push_back(0.5);
    ptBinAssoc_.push_back(1000);
    
  }

  else if ( cutOpt == 500000) {
    coneSize_ = 0.3;
    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);

    ptBin_.push_back(50);
    ptBin_.push_back(10000);

    jetPtBin_.push_back(20);
    jetPtBin_.push_back(10000);
   
    ptBinAssoc_.push_back(0.5);
    ptBinAssoc_.push_back(1000);
    
  }
  else if ( cutOpt == 500020) {
    coneSize_ = 0.3;

    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);

    ptBin_.push_back(50);
    ptBin_.push_back(10000);

    jetPtBin_.push_back(20);
    jetPtBin_.push_back(10000);
   
    ptBinAssoc_.push_back(0.5);
    ptBinAssoc_.push_back(1000);

  }
  else if ( cutOpt == 500025) {
    coneSize_ = 0.3;

    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);

    ptBin_.push_back(50);
    ptBin_.push_back(10000);

    jetPtBin_.push_back(25);
    jetPtBin_.push_back(10000);

    ptBinAssoc_.push_back(0.5);
    ptBinAssoc_.push_back(1000);

  }

  else if ( cutOpt == 500030) {
    coneSize_ = 0.3;

    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);

    ptBin_.push_back(50);
    ptBin_.push_back(10000);

    jetPtBin_.push_back(30);
    jetPtBin_.push_back(10000);

    ptBinAssoc_.push_back(0.5);
    ptBinAssoc_.push_back(1000);

  }

  else if ( cutOpt == 603010) {
    coneSize_ = 0.3;

    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);

    ptBin_.push_back(60);
    ptBin_.push_back(10000);

    jetPtBin_.push_back(30);
    jetPtBin_.push_back(10000);

    ptBinAssoc_.push_back(1);
    ptBinAssoc_.push_back(2000);
  }

  else if ( cutOpt == 603011) {
    coneSize_ = 0.3;

    centBin_.clear();
    centBin_.push_back(0);
    centBin_.push_back(4);
    centBin_.push_back(12);
    centBin_.push_back(20);
    centBin_.push_back(40);

    ptBin_.push_back(60);
    ptBin_.push_back(10000);

    jetPtBin_.push_back(30);
    jetPtBin_.push_back(10000);

    ptBinAssoc_.push_back(1);
    ptBinAssoc_.push_back(2);
    ptBinAssoc_.push_back(4);
    ptBinAssoc_.push_back(8);
    ptBinAssoc_.push_back(16);
    ptBinAssoc_.push_back(1000);

  }



  else 
    cout << "  we dont have such template option " << endl;
  
  

}




/*
float CutAndBinCollection::getHoECut(   float percentBin=false; float et ) {  // 100% centrality used   
float thehoe = 0.1;
if ( percentBin <= 20 ) {   // should change univHoEnCut  accordingly
if         ( et <=30 )                thehoe = 0.15;
else                                  thehoe = 0.1;
}
if ( percentBin > 20 ) {
if         ( et <=30 )                thehoe = 0.1;
`else                                  thehoe = 0.05;
}

cout << endl << " centrality = " << percentBin << "%" << "    et = " << et << "     hoeCut = " << thehoe << endl;
return thehoe;
}

*/


void addCentralityFriend(TTree *tSig, TTree *tData,TCut selectionCut)
{
   //copied from /d101/yjlee/HIPhoton/ana/photonAna2011/common.h
   static int counter=0;
   TH1D *hSigCent = new TH1D("hSigCent","",40,-0.5,39.5);
   TH1D *hDataCent = new TH1D("hDataCent","",40,-0.5,39.5);

   hSigCent->SetLineColor(2);
   tSig->Project("hSigCent","cBin",selectionCut);
   tData->Project("hDataCent","cBin",selectionCut);
   hDataCent->Scale(1./hDataCent->GetEntries());
   hSigCent->Scale(1./hSigCent->GetEntries());
   hDataCent->Divide(hSigCent);
   TNtuple *nt = new TNtuple(Form("ntCentFriend%d",counter),"","cBinWeight");

   Int_t cBin;
   tSig->SetBranchAddress("cBin",&cBin);

   for (int i=0;i<tSig->GetEntries();i++)
      {
	 tSig->GetEntry(i);
	 int bin = hDataCent->FindBin(cBin);
	 //cout <<cBin<<" "<<hDataCent->GetBinContent(bin)<<endl;                                                                                                                                                    
	 nt->Fill(hDataCent->GetBinContent(bin));
      }
   counter++;
   delete hSigCent;
   delete hDataCent;
   tSig->AddFriend(nt);
}


void getNColl( float* ncoll) {

ncoll[0] = 1747.86 ; 
ncoll[1] = 1567.53 ; 
ncoll[2] = 1388.39 ; 
ncoll[3] = 1231.77 ; 
ncoll[4] = 1098.2 ; 
ncoll[5] = 980.439 ; 
ncoll[6] = 861.609 ; 
ncoll[7] = 766.042 ; 
ncoll[8] = 676.515 ; 
ncoll[9] = 593.473 ; 
ncoll[10] = 521.912 ; 
ncoll[11] = 456.542 ; 
ncoll[12] = 398.546 ; 
ncoll[13] = 346.647 ; 
ncoll[14] = 299.305 ; 
ncoll[15] = 258.344 ; 
ncoll[16] = 221.216 ; 
ncoll[17] = 188.677 ; 
ncoll[18] = 158.986 ; 
ncoll[19] = 134.7 ; 
ncoll[20] = 112.547 ; 
ncoll[21] = 93.4537 ; 
ncoll[22] = 77.9314 ; 
ncoll[23] = 63.5031 ; 
ncoll[24] = 52.0469 ; 
ncoll[25] = 42.3542 ; 
ncoll[26] = 33.9204 ; 
ncoll[27] = 27.3163 ; 
ncoll[28] = 21.8028 ; 
ncoll[29] = 17.2037 ; 
ncoll[30] = 13.5881 ; 
ncoll[31] = 10.6538 ; 
ncoll[32] = 8.35553 ; 
ncoll[33] = 6.40891 ; 
ncoll[34] = 5.13343 ; 
ncoll[35] = 3.73215 ; 
ncoll[36] = 3.06627 ; 
ncoll[37] = 2.41926 ; 
ncoll[38] = 2.11898 ; 
 ncoll[39] = 1.76953 ; 
 
}



fitResult doFit(TH1D* hSig=0, TH1D* hBkg=0, TH1D* hData1=0, float varLow=0.001, float varHigh=0.028, bool drawLeg=true) {
   
   TH1D* hDatatmp = (TH1D*)hData1->Clone(Form("%s_datatmp",hData1->GetName()));
   int nBins = hDatatmp->GetNbinsX();
   histFunction2 *myFits = new histFunction2(hSig,hBkg);
   TF1 *f = new TF1("f",myFits,&histFunction2::evaluate,varLow,varHigh,2);
   f->SetParameters( hDatatmp->Integral(1,nBins+1), 0.3);
   f->SetParLimits(1,0,1);
   hDatatmp->Fit("f","LL M O Q","",varLow,varHigh);
   hDatatmp->Fit("f","LL M O Q","",varLow,varHigh);

   fitResult res;
   res.nSig =0;
   double nev = f->GetParameter(0);
   double ratio = f->GetParameter(1);
   double ratioErr = f->GetParError(1);
   res.nSig    = nev * ratio;
   res.nSigErr = nev * ratioErr;
   res.chisq = (double)f->GetChisquare()/ f->GetNDF();
   
   TH1F *hSigPdf = (TH1F*)hSig->Clone(Form("%s_tmp",hSig->GetName()));
   hSigPdf->Scale(res.nSig/hSigPdf->Integral(1,nBins+1));

   TH1F *hBckPdf = (TH1F*)hBkg->Clone(Form("%s_tmp",hBkg->GetName()));
   hBckPdf->Scale((nev-res.nSig)/hBckPdf->Integral(1,nBins+1));

   double ss1 = hSigPdf->Integral(1, hSigPdf->FindBin(0.00999),"width");
   double bb1 = hBckPdf->Integral(1, hBckPdf->FindBin(0.00999),"width");
   //   cout <<"  hte bin = " <<hSigPdf->FindBin(0.00999) << endl;
   res.purity010 = ss1/(ss1+bb1);
   cout << "purity = " << res.purity010 << endl;
   hSigPdf->Add(hBckPdf);
   handsomeTH1(hSigPdf);
   mcStyle(hSigPdf);
   sbStyle(hBckPdf);
   cleverRange(hSigPdf,1.5);
   hSigPdf->SetNdivisions(505);

   hSigPdf->SetYTitle("Entries");
   hSigPdf->DrawCopy("hist");
   hBckPdf->DrawCopy("same hist");
   hData1->DrawCopy("same");
   TH1D* temphSigPdf = (TH1D*)hSigPdf->Clone("temp1");
   TH1D* temphBckPdf = (TH1D*)hBckPdf->Clone("temp2");
   if(drawLeg){
      TLegend *t3=new TLegend(0.5402006,0.5963235,0.9186019,0.7853466,NULL,"brNDC");
      //      t3->AddEntry(hData1,"Pb+Pb  #sqrt{s}_{_{NN}}=2.76 TeV","pl");
      t3->AddEntry(temphSigPdf,"Signal","lf");
      t3->AddEntry(temphBckPdf,"Background","lf");
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();
      //    drawCMS2011(0.53,0.9,150,16);
   }
   

   //   delete hSigPdf;                                                                                                                                                                                             
   //   delete hBckPdf;                                                                                                                                                                                             

   //  TFile* hout = new TFile("histo.root","recreate");
   //  hSigPdf->Write();
   //  hBckPdf->Write();
   //  hData1->Write();
   //  hout->Close();

   
   return res;

}



#endif
