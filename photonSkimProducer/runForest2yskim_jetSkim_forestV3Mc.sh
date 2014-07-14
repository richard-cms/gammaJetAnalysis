#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/HiForest4/hiForest_Photon40_GR_R_53_LV6_25Feb2014_1530CET_Track8_Jet15.root",
#                                   std::string MinbiasFname = "forestFiles/HiForest4/skim_collId_kHIDATA_jetAlgo_akPu3PF_HIMinBias2011_GR_R_53_LV6_CMSSW_5_#
#                                   float cutphotonPt  = 35,
#                                   sampleType colli=kHIDATA,
#                                   TString jetAlgo="akPu3PF",
#                                   bool doMix = true,
#                                   TString triggerSelection="",
#                                   bool doJetResCorrection = 0, 
#                                   int smearingCentBin = -1, //0=0-10%, 1=10-30%, 2=30-50%, 3=50-100%, 4=0-30%, 5=30-100%  : Jet pT and phi smearing!
#                                   bool useGenJetColl = 0
#                                   )


#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5

kHIMC=1
kPPMC=3
# pbpb MC
inputSkim="forestFiles/HiForest4/skim_collId_kHIMC_jetAlgo_akPu3PF_HiForest_HYDJET_Track8_Jet21_STARTHI53_LV1_merged_forest_0.root"
for input in "forestFiles/pbpb/PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root" "forestFiles/pbpb/PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root"
do
    root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("'$input'", "'$inputSkim'", 20,   '$kHIMC', "akPu3PF", 1)'
echo "PbPb MC"
done

input="forestFiles/pp/pp2760_pythia_allQCDPhoton30_CMSSW538HIp2.root"
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("'$input'", "No file", 20,   '$kPPMC', "akPu3PF", 0)'

