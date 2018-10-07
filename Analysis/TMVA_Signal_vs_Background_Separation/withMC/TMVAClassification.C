#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification( TString myMethodList = "" )
{
   TMVA::Tools::Instance();
   // --------------------------------------------------------------------------------------------------

   TFile *input0 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_VBFHToBB_M_125_.root");
   TFile *input1 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT200to300_TuneCP5_.root");
   TFile *input2 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT300to500_TuneCP5_.root");
   TFile *input3 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT500to700_TuneCP5_.root");
   TFile *input4 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT700to1000_TuneCP5_.root");
   TFile *input5 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1000to1500_TuneCP5_.root");
   TFile *input6 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1500to2000_TuneCP5_.root");
   TFile *input7 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT2000toInf_TuneCP5_.root");
   TTree *signalTree      = (TTree*)input0->Get("Sig");
   TTree *background1     = (TTree*)input1->Get("Bkg");
   TTree *background2     = (TTree*)input2->Get("Bkg");
   TTree *background3     = (TTree*)input3->Get("Bkg");
   TTree *background4     = (TTree*)input4->Get("Bkg");
   TTree *background5     = (TTree*)input5->Get("Bkg");
   TTree *background6     = (TTree*)input6->Get("Bkg");
   TTree *background7     = (TTree*)input7->Get("Bkg");
   TFile* outputFile = TFile::Open("TMVA.root", "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   dataloader->SetWeightExpression("weight");
   dataloader->AddVariable( "mqq",                    "Mqq", "units", 'F' );
   dataloader->AddVariable( "detaqq",                "dETAqq", "units", 'F' );
   dataloader->AddVariable( "dphiqq",                "dPHIqq", "units", 'F' );
   dataloader->AddVariable( "btgb1_D",               "Btg_1b", "units", 'F' );
   dataloader->AddVariable( "btgb2_D",               "Btg_2b", "units", 'F' );
   dataloader->AddVariable( "qtgq1",                 "Qtg_1q", "units", 'F' );
   dataloader->AddVariable( "qtgq2",                 "Qtg_2q", "units", 'F' );
   dataloader->AddVariable( "NJ_ingap",                'I');
   dataloader->AddVariable( "pt_All",                "Summ_PT", "units", 'F' );
   dataloader->AddVariable( "pz_All",                "Summ_PZ", "units", 'F' );
   dataloader->AddVariable( "Njet_20",                'I');
   dataloader->AddVariable( "HTT_rest_20",           "HTT_Rest_PTgt20", "units", 'F' );
   dataloader->AddVariable( "E_rest_20",           "E_Rest_PTgt20", "units", 'F' );
   dataloader->AddSpectator( "minvbb",               "MinvBB", "units", 'F' );

   dataloader->AddSignalTree    ( signalTree);
   dataloader->AddBackgroundTree( background1);
   dataloader->AddBackgroundTree( background2);
   dataloader->AddBackgroundTree( background3);
   dataloader->AddBackgroundTree( background4);
   dataloader->AddBackgroundTree( background5);
   dataloader->AddBackgroundTree( background6);
   dataloader->AddBackgroundTree( background7);

// Book BDT
//   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
//                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

// From AN
     factory->BookMethod(dataloader,TMVA::Types::kBDT, "BDTG",
//                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
                           "!H:!V:NTrees=150:MinNodeSize=8.0%:MaxDepth=3:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:BaggedSampleFraction=0.6:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining");




// To Training Testing and Evaluatiing Facory Methods
   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();

   outputFile->Close();
   delete factory;
   delete dataloader;

// Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui("TMVA.root");

   return 0;
}
