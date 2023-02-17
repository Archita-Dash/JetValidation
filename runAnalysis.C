class AliEmcalJetTask;
class AliEmcalCorrectionTask;
class AliAnalysisTaskEmcalJetSample;
class AliESDInputHandler;
class AliAODInputHandler;
class AliVEvent;
class AliAnalysisManager;
class AliPhysicsSelectionTask;
class AliCentralitySelectionTask;
class AliEmcalCorrectionTask;
class AliEmcalJetTask;
class AliAnalysisTaskRho;
//class AliAnalysisTaskHFJetIPQA;
class AliAnalysisGrid;
class AliAnalysisAlien;

class AliAnalysisTaskEmcalJetValidation;

#include "AliAnalysisTaskEmcalJetValidation.h"
#include "AddTaskEmcalJetValidation.C"



#ifdef __CLING__
R__ADD_INCLUDE_PATH($ALICE_PHYSICS)
R__ADD_INCLUDE_PATH($ALICE_ROOT)
#include <ANALYSIS/macros/AddTaskPIDResponse.C>
#include <OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C>
#include <AliAnalysisManager.h>
#include <AliPIDResponse.h>
//#include <AddbjetsTask.C>
#include <AliAnalysisTaskPIDResponse.h>
#include <AliAODInputHandler.h>
#include <AliAnalysisAlien.h>
//#include <"AliCentrality.h">
#include "OADB/macros/AddTaskPhysicsSelection.C"
#include "OADB/macros/AddTaskCentrality.C"
#include "PWGPP/PilotTrain/AddTaskCDBconnect.C"
#include "PWGJE/EMCALJetTasks/macros/AddTaskRhoNew.C"
#include "PWGJE/EMCALJetTasks/macros/AddTaskEmcalJetSample.C"
#include "PWGHF/vertexingHF/macros/AddTaskImproveITSCVMFS.C"
//#include "AliAnalysisTaskParticleInJet.h"

#include <TMacro.h>
#include <TSystem.h>
#include <TChain.h>
#include <TString.h>
#include <TList.h>



#endif

void runAnalysis()
{
    // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
    Bool_t local = kTRUE;
    // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
    //Bool_t gridTest = kFALSE;

    // since we will compile a class, tell root where to look for headers
    #if !defined (CINT) || defined (CLING)
        gInterpreter->ProcessLine(".include $ROOTSYS/include");
        gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
        gInterpreter->ProcessLine(".include $ALICE_PHYSICS/include");

    #else
   	gROOT->ProcessLine(".include $ROOTSYS/include");
    	gROOT->ProcessLine(".include $ALICE_ROOT/include");
    #endif


    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskEmcalJetValidation");
    //AliAODInputHandler *aodH = new AliAODInputHandler();
    //mgr->SetInputEventHandler(aodH);

    AliESDInputHandler* pESDHandler = AliAnalysisTaskEmcal::AddESDHandler();
    mgr->SetInputEventHandler(pESDHandler);

   //TMacro PIDadd(gSystem->ExpandPathName("ANALYSIS/macros/AddTaskPIDResponse.C"));
   //AliAnalysisTaskPIDResponse* PIDresponseTask = reinterpret_cast<AliAnalysisTaskPIDResponse*>(PIDadd.Exec());

   //AliAnalysisTaskPIDResponse *PIDResponse = AddTaskPIDResponse(kTRUE, kFALSE, kTRUE,"3"); // isMC, autoMCesd, tuneOnData, recoPass, cachePID, detResponse

   //PIDResponse->SetTuneOnData(kTRUE,1,"Pass1"); //requesting a MC tune (first argument set to kTRUE), for reconstruction pass 3 of the data. (Every now and then data is reprocessed and every of this data sets is called 'pass i' with i increasing for each.) the newest one for LHC16k (the data I'm now using) seems to be pass3

   //PIDResponse->SelectCollisionCandidates((AliVEvent::kINT7));


  //TMacro multSelection(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"));
  //AliMultSelectionTask* multSelectionTask = reinterpret_cast<AliMultSelectionTask*>(multSelection.Exec());

   //Task to find jets and store them in a container

  AliTaskCDBconnect *taskCDB = AddTaskCDBconnect();
  taskCDB->SetFallBackToRaw(kTRUE);			// this task does some important calibration

  //AKT jet finding: pp Detector Level
  //AliEmcalJetTask *pJetTaskAKT = AliEmcalJetTask::AddTaskEmcalJet("usedefault", "", AliJetContainer::antikt_algorithm, 0.4, AliJetContainer::kChargedJet, 0.15, 0.30, 0.005, AliJetContainer::pt_scheme, "DetLevelJets",1., kFALSE, kFALSE);
  //pJetTaskAKT->SelectCollisionCandidates(AliVEvent::kINT7);
  //pJetTaskAKT->GetTrackContainer(0)->SetTrackFilterType(AliEmcalTrackSelection::kCustomTrackFilter);
  //pJetTaskAKT->GetTrackContainer(0)->SetESDFilterBits( 1<<4 | 1<<9);

  //TString kJetAKT_DetLevel_Name = pJetTaskAKT->GetName();
  //cout<<endl<<"AKT DETECTOR LEVEL "<<kJetAKT_DetLevel_Name.Data()<<endl<<endl;


  //  AliEmcalJetTask *pChJet04TaskMC = AliEmcalJetTask::AddTaskEmcalJet("mcparticles", "", AliJetContainer::antikt_algorithm, 0.4, AliJetContainer::kChargedJet, 0.15, 0.3, 0.01, AliJetContainer::E_scheme, "Jet", 1., kFALSE, kFALSE); // Data<->MC

   // TMacro PIDadd(gSystem->ExpandPathName("ANALYSIS/macros/AddTaskPIDResponse.C"));

        //AliAnalysisTaskPIDResponse* PIDresponseTask = reinterpret_cast<AliAnalysisTaskPIDResponse*>(PIDadd.Exec());

   /*TMacro multSelection(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"));
    AliMultSelectionTask* multSelectionTask = reinterpret_cast<AliMultSelectionTask*>(multSelection.Exec());*/

   /* Float_t centrality(0);
    AliMultSelection *multSelection =static_cast<AliMultSelection*>(fAOD->FindListObject("MultSelection"));
    if(multSelection) centrality = multSelection->GetMultiplicityPercentile("V0M");*/

    // compile the class (locally)
    //gROOT->LoadMacro("AliAnalysisTaskEmcalJetValidation.cxx++g");
    // load the addtask macro
    //gROOT->LoadMacro("AddTaskEmcalJetValidation.C");


    // create an instance of your analysis task
    AliAnalysisTaskEmcalJetValidation *taskJet = AddTaskEmcalJetValidation("", "config.json");

    //Printf("Check done %i",__LINE__);

    if(!mgr->InitAnalysis()) return;
    mgr->SetDebugLevel(10);
    mgr->PrintStatus();
    mgr->SetUseProgressBar(1, 25);

    if(local) {
        // if you want to run locally, we need to define some input
        TChain* chain = new TChain("esdTree");
        // add a few files to the chain (change this so that your local files are added)
        chain->Add("AliESDs.root");
        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskEmcalJetValidation.cxx AliAnalysisTaskEmcalJetValidation.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskEmcalJetValidation.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20211006-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");
        // select the input data
        alienHandler->SetGridDataDir("/alice/data/2018/LHC18b/000285396/pass1/18000285396019.111");
        alienHandler->SetDataPattern("ESD/*/AliESDs.root");
        // MC has no prefix, data has prefix 000
        alienHandler->SetRunPrefix("000");
        // runnumber
        alienHandler->AddRunNumber(285396);
        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(40);
        alienHandler->SetExecutable("myTask.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("myTask.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with kTRUE to merge on grid
        // after re-running the jobs in SetRunMode("terminate")
        // (see below) mode, set SetMergeViaJDL(kFALSE)
        // to collect final results
        alienHandler->SetMaxMergeStages(1);
        alienHandler->SetMergeViaJDL(kFALSE);		//kTRUE: when running the job and set kFALSE when downloading the output once job is done

        // define the output folders
        alienHandler->SetGridWorkingDir("myWorkingDir");
        alienHandler->SetGridOutputDir("myOutputDir");

        // connect the alien plugin to the manager
      /*  mgr->SetGridHandler(alienHandler);
        if(gridTest) {
            // specify on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
            // else launch the full grid analysis
            alienHandler->SetRunMode("full");
            mgr->StartAnalysis("grid");
        }*/
    }
}
