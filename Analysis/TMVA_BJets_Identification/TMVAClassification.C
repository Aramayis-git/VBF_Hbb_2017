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

   TFile *input = TFile::Open("For_BB_MVA_Training.root");
   TTree *signalTree      = (TTree*)input->Get("bb");
   TTree *background1     = (TTree*)input->Get("qq");
   TFile* outputFile = TFile::Open("TMVA.root", "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   dataloader->SetWeightExpression("weight");
   dataloader->AddVariable( "pt",                "PT", "units", 'F' );
   dataloader->AddVariable( "pt_ord",               'I' );
   dataloader->AddVariable( "feta",             "ETA", "units", 'F' );
   dataloader->AddVariable( "feta_ord",             'I' );
   dataloader->AddVariable( "btg_D",             "BTG_Deep", "units", 'F' );
   dataloader->AddVariable( "btg_D_ord",            'I' );
//   dataloader->AddVariable( "btg",             "BTG", "units", 'F' );
//   dataloader->AddVariable( "btg_ord",            'I' );
   dataloader->AddVariable( "puid",             "PUID", "units", 'F' );

   dataloader->AddSignalTree    ( signalTree );
   dataloader->AddBackgroundTree( background1 );

// From AN
     factory->BookMethod(dataloader,TMVA::Types::kBDT, "BDTG",
                         "!H:!V:NTrees=120:MinNodeSize=8.0%:MaxDepth=3:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:BaggedSampleFraction=0.6:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining");

// To Training Testing and Evaluatiing Facory Methods
   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();

   outputFile->Close();
   delete factory;
   delete dataloader;

// Launch the GUI for the root macros
//   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}
