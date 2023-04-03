/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskEmcalJetValidation_H
#define AliAnalysisTaskEmcalJetValidation_H

#include "AliAnalysisTaskEmcalJet.h"
#include "AliAnalysisTaskSE.h"
#include "AliPIDResponse.h"
//#include "AliAnalysisTaskParticleInJet.h"

class AliEmcalJet;
class AliAODVertex;
class AliAODTrack;
class AliAODEvent;
class TList;
class TH1F;
class TH2F;
class AliPIDResponse;
class AliEmcalList;
class AliEmcalJetFinder;
class AliAODMCParticle;
class AliMCEvent;
class AliOADBContainer;
#include "AliFJWrapper.h"

class AliAnalysisTaskEmcalJetValidation : public AliAnalysisTaskEmcalJet
{
public:
                            AliAnalysisTaskEmcalJetValidation();
                            AliAnalysisTaskEmcalJetValidation(const char *name);
    virtual                 ~AliAnalysisTaskEmcalJetValidation();

    virtual void            UserCreateOutputObjects();
    virtual void            UserExec(Option_t* option);
    virtual void            Terminate(Option_t* option);

private:
    AliAODEvent*            fAOD;           //! input event
    TList*                  fOutputList;    //! output list
    TH1F*                   fHistJetPt;        //! dummy histogram
    TH1F*			              fHistNEvents;   //! histogram for total number of events
    AliEmcalJet*		        GetPerpendicularPseudoJet (AliEmcalJet*jet_in , bool rev); //!
    AliEmcalJet*		        jetrec;	  //!
    AliEmcalJet*		        jetmatched;	  //!

    AliJetContainer*        jetconrec; //!
    AliJetContainer*        jetcongen; //!
    Float_t                 fJetRecPt; 	//!
    TH1F*			              fHistjet; //!




    AliAnalysisTaskEmcalJetValidation(const AliAnalysisTaskEmcalJetValidation&); // not implemented
    AliAnalysisTaskEmcalJetValidation& operator=(const AliAnalysisTaskEmcalJetValidation&); // not implemented

    ClassDef(AliAnalysisTaskEmcalJetValidation, 1);
};

#endif
