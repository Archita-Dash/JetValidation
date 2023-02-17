class AliAnalysisDataContainer;

#include "TString.h"
#include "AliAnalysisTaskEmcalJetValidation.h"
#include "AliAnalysisManager.h"
//#include "AliAnalysisTaskParticleInJet.h"

AliAnalysisTaskEmcalJetValidation* AddTaskEmcalJetValidation(
   const char *ntracks                        = "usedefault",
   const char *nclusters                      = "usedefault",
   const AliJetContainer::EJetAlgo_t jetAlgo  = AliJetContainer::antikt_algorithm,
   const Double_t jetradius                   = 0.4,
   const AliJetContainer::EJetType_t jetType  = AliJetContainer::kFullJet,
   const Double_t minTrPt                     = 0.15,
   const Double_t minClPt                     = 0.30,
   const Double_t ghostArea                   = 0.005,
   const AliJetContainer::ERecoScheme_t reco  = AliJetContainer::pt_scheme,
   const Double_t minJetPt                    = 0.,
   const char *suffix                         = ""
 )
 {
   return AliAnalysisTaskEmcalJetValidation::AliAnalysisTaskEmcalJetValidation(ntracks, nclusters, jetAlgo, radius, jetType, minTrPt, minClPt, ghostArea,
                                           reco, minJetPt,suffix);
 }

 Printf("Check done %i",__LINE__);
    // get the manager via the static access member. since it's static, you don't need
    // an instance of the class to call the function
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }

    // get the input event handler, again via a static method.
    // this handler is part of the managing system and feeds events
    // to your task
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }


    // by default, a file is open for writing. here, we get the filename
    TString fileName = AliAnalysisManager::GetCommonFileName();
    fileName += ":MyTask";      // create a subfolder in the file
    // now we create an instance of your task
    AliAnalysisTaskEmcalJetValidation* task = new AliAnalysisTaskEmcalJetValidation(name.Data());
    if(!task) return 0x0;


    // Setup input containers
    //==============================================================================
    Printf("%s :: Setting up input containers.",taskname.Data());
    AliParticleContainer *trackCont  = task->AddParticleContainer(ntracks.Data());
    AliClusterContainer *clusterCont = task->AddClusterContainer(nclusters.Data());
    TString strType(type.Data());
    AliJetContainer *jetCont = task->AddJetContainer(njets.Data(),strType,jetradius);

    Printf("Check done %i",__LINE__);

    if(jetCont) {
      jetCont->SetRhoName(nrho.Data());
      jetCont->ConnectParticleContainer(trackCont);
      jetCont->ConnectClusterContainer(clusterCont);
      //DefineCutsTaskpp(jetCont, jetradius);
    }
    Printf("Check done %i",__LINE__);

    // if(isMC){
    //   AliParticleContainer *trackContMC   = task->AddParticleContainer(ntracksMC.Data());
    //   AliJetContainer *jetContMC = task->AddJetContainer(njetsMC.Data(),strType,jetradius);
    //
    //   if(jetContMC) {
    //     jetContMC->SetRhoName(nrhoMC.Data());
    //     jetContMC->ConnectParticleContainer(trackContMC);
    //     jetContMC->SetIsParticleLevel(kTRUE);
    //     //jetContMC->SetMaxTrackPt(1000);
    //     //DefineCutsTaskpp(jetContMC, jetradius);
    //     }
    // }

   //=====================================================================================
    Printf("Check done %i",__LINE__);
    mgr->AddTask(task);
    mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
    mgr->ConnectOutput(task,1,mgr->CreateContainer("MyOutputContainer", TList::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    Printf("Check done %i",__LINE__);




    return task;

}
