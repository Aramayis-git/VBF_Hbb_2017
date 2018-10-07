
# Instruction for VBF_Hbb 2017  (Only for SingleBTag as DoubleBTag is under development)

**************************************************************************************************
# Stage 1 (from CMSSW area, NO need to ReRun just go to Stage 2)    !!! can be skipped tiil stage 2

# 1. CMSSW code instalation for MC and Data analysis: Event preselection & NTuples making

cmsrel CMSSW_9_4_6_patch1
cd CMSSW_9_4_6_patch1/src
cmsenv
cp -r /afs/cern.ch/user/t/tumasyan/public/VBF_Hbb_2017/Data_src/* .
scram b

# 1.a  Event preselection of 2017F Data (7.73 fb-1)

# Input parameters and algorithms for preselection in
PreSelection/Single_BTg_Filter/src/Input_Parameters.txt
# Source file is
PreSelection/Single_BTg_Filter/src/Single_BTg_Filter.cc
# Python configuration to run (which also adds QGTagger) is
PreSelection/JOB/SingleB_PreSelection.py
# Running crab job
cd PreSelection/JOB/
python Crab_Single.py

# 1.b  Making NTuples  (7-PT leading jets with PT>20, eta<4.7 and passing loose PuId     and    Other variables including NJets,HTT,...)

# Source file is 
Analysis/Local/src/Test_On_Data.cc
# Python configuration to run
Test/On_Data/Test_On_Data_*.py
# script to prepare batch jobs is
Test/On_Data/Test_Execution.csh
# Root files with Ntuples are located in                             *** If you want to use ready NTuples
/eos/user/t/tumasyan/Hbb_2017/Preselected_singleB_Data/Test_Results/


# 2. CMSSW code instalation for MC analysis: Event preselection & NTuples making, including truth information

(Not complete yet)

# Root files with Ntuples are located in                             *** If you want to use ready NTuples (weights after PuReWeighting are included)
/eos/user/t/tumasyan/Hbb_2017/Preselected_singleB_MC/Training_Results/
# Root file for Signal (VBF_Hbb) is
/eos/user/t/tumasyan/Hbb_2017/Preselected_singleB_MC/Training_Results/Training__VBFHToBB_M_125__.root


**************************************************************************************************
Stage 2 (no need of CMSSW area, just Root including TMVA package)

# Training with TMVA: Jet combination and Signal_vs_Background discrimination 
# Samples (Root files with NTuples: 7-PT leading jets and  Other variables) are in
Preselected_NTuples/
# Where
Training__Training5perc__.root      is 5% of Data for MVA training
Training__Training__.root           is full preselected Data ~ 7.73 fb-1
Training__VBFHToBB_M_125__.root     is VBF_Hbb MC preselected sample
... NTuples of other MC samples

# For Analysis
cd Analysis
# 1.   PuReWeighting results in
Pu_ReWeight/

# 2. b-jets identification in signal process with TMVA
cd TMVA_BJets_Identification
# Making Ntuples for TMVA training
root -l Sort.C
# Training MVA (Gradient BDT method)
root -l TMVAClassification.C
# Using TMVA Graphical User Interface
root -l
TMVA::TMVAGui("TMVA.root")
# dataset directory is ready (created) to be used for b-jets selection
# Checking Final selection performance with TMVA
root -l TMVA_Training_Result.C
# Checking Final selection performance with b-tag discriminator
root -l High_btag_Selected_Jets.C
# Comparision
root -l Compare.C


# 3.    Making Ntuples for Sig vs Bkg Discrimination and Final Results
cd ../Making_Ntuples_For_SigBkgDiscrimination

For data derived approach
cd Data_Derived/
cp -r ../TMVA_BJets_Identification/dataset .
root -l Data_Derived.C

For MC derived approach
cd MC_Derived/
cp -r ../TMVA_BJets_Identification/dataset .
root -l MC_Derived.C


# 4.    Signal vs Background discrimination using TMVA and final results
#For data derived approach
cd ../../TMVA_Signal_vs_Background_Separation/withData
# MVA (Gradient BDT) Training
root -l TMVAClassification.C
# Creating Mbb for Signal_MC (VBF and ggF), Bakground (5% of Data) and Observed (Full Data) based on Trained BDT
# output will be Mbb_All.root, which will be used in fits (estimation of deviation from pure-background model)
root -l Mbb_For_Sig_Bkg_Obs.C

# Comparision of BDT responce for Signal_MC (VBF_Hbb_MC) and observed (Data_2017F)
root -l bdt_res.C
root -l Compare.C

#For MC derived approach
cd ../../TMVA_Signal_vs_Background_Separation/withMC
# MVA (Gradient BDT) Training
root -l TMVAClassification.C   (or dataset from dtat-derived training can be used - cp -r ../WithData/dataset .)
# Creating Mbb for Signal_MC (VBF and ggF) and Bakground (MC-QCD + other samples)
root -l Mbb_For_Sig_Bkg.C
# Comparision of BDT responce for Signal_MC (VBF_Hbb_MC) and background (MC-QCD)
root -l bdt_res.C
root -l Compare.C


# 5. Mbb correlation

root -l mbb_Correlation.C  (takes a while - 2-3 min)

#use root macros output in corr_res.C
root -l corr_res.C





# Insttruction for git

$ git clone ssh://git@github.com/CMSVBFHbb1718/VBF_Hbb_2017_18

# eddit, add, remove files
$ #creating/editing <file>
$ git rm <file>
#you can see your change 
$ git status -su

# add changes
$ git add <file>
$ git commit -m "comment in your change"
$ git pull
$ git push 

