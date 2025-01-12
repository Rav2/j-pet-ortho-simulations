/// @file event.h
/// @author Rafal Maselek <rafal.maselek@ncbj.gov.pl>
/// @date 13.07.2017
#ifndef EVENT_H
#define EVENT_H
#include "TLorentzVector.h"
#include "TObject.h"
#include "TTree.h"
#include <vector>

///
/// \brief The DecayType enum Specifies the type of decay in which the event was produced.
///
enum DecayType
{
    WRONG = 0,
    ONE = 1,
    TWO = 2,    
    THREE = 3,
    TWOandONE = 4,
    TWOandN = 5
};

///
/// \brief The Event class Class holding information about products of one decay.
///
class Event : public TObject
{
    public:
        Event();
        Event(std::vector<TLorentzVector*>* emissionCoordinates, std::vector<TLorentzVector*>* fourMomentum, double weight, DecayType type);
        Event(std::vector<TLorentzVector> &sourcePos, std::vector<TLorentzVector> &pos, std::vector<TLorentzVector> &momentum,\
        std::vector<double> &phi, std::vector<double> &theta, std::vector<bool> &cutPassing, std::vector<bool> &primary,\
        std::vector<double> &edep, std::vector<double> &edepSmear, long Id, int decayType);
        Event(const Event& est);
        Event& operator=(const Event &est);
        virtual ~Event();
        //setters and getters
        inline TLorentzVector* GetEmissionPointOf(const unsigned index) const
            {return index<fEmissionPoint_.size() ? const_cast<TLorentzVector*>(&fEmissionPoint_[index]) : NULL;}
        inline TLorentzVector* GetFourMomentumOf(const unsigned index) const
            {return index<fFourMomentum_.size() ? const_cast<TLorentzVector*>(&fFourMomentum_[index]) : NULL;}
        inline int GetNumberOfDecayProducts() const {return fFourMomentum_.size();}
        inline TLorentzVector* GetHitPointOf(const unsigned index) const
            {return index<fHitPoint_.size() ? const_cast<TLorentzVector*>(&fHitPoint_[index]) : NULL;}
        inline bool GetCutPassingOf(const unsigned index) const
            {return index<fCutPassing_.size() ? fCutPassing_[index] : false;}
        inline bool GetPrimaryPhoton(const unsigned index) const
            {return index<fPrimaryPhoton_.size() ? fPrimaryPhoton_[index] : false;}
        inline double GetWeight() const {return fWeight_;}
        inline DecayType GetDecayType() const {return fDecayType_;}
        inline bool GetPassFlag() const {return fPassFlag_;}
        inline double GetHitPhiOf(const unsigned index) const {return fHitPhi_[index];}
        inline double GetHitThetaOf(const unsigned index) const {return fHitTheta_[index];}
        inline double GetEdepOf(const unsigned index) const {return fEdep_[index];}
        inline double GetEdepSmearOf(const unsigned index) const {return fEdepSmear_[index];}
        inline void SetFourMomentumOf(const unsigned index, TLorentzVector& vector)
        { if(index < fFourMomentum_.size()) fFourMomentum_[index] = TLorentzVector(vector);}
        inline void SetCutPassing(const unsigned ii, bool val)
            {if(ii<fCutPassing_.size()) fCutPassing_[ii]=val;}
        inline void SetPrimaryPhoton(const unsigned ii, bool isPrimary) {fPrimaryPhoton_.at(ii)=isPrimary;}
        inline void SetEdepOf(const unsigned ii, double val) {fEdep_[ii]=val;}
        inline void SetEdepSmearOf(const unsigned ii, double val) {fEdepSmear_[ii]=val;}

        //set fPassFlag_ by checking values in fCutPassing_
        void DeducePassFlag();
        //calculates hit point of gammas on a detectors surface and fills fHitTheta_ and fHitPhi_ histograms
        // angles are calculated in reference to the center of the reference system's center !!!
        void CalculateHitPoints(double R, double L);
        //number of event
        long fId;
        //ROOT stuff
        ClassDef(Event, 18)

    private:
        static long fCounter_; //static variable incremented with every call of a constructor (but not copy constructor)
        std::vector<TLorentzVector> fEmissionPoint_; //x, y, z, t(irrelevant) [mm and s]
        std::vector<TLorentzVector> fFourMomentum_; //pX, pY, pZ, E [MeV/c and MeV]
        std::vector<bool> fCutPassing_; //indicates if gamma failed passing through cuts
        double fWeight_; //weight of the event
        DecayType fDecayType_; //type of the event
        bool fPassFlag_; //if true, event can be reconstructed -- all necessary gammas passed through cuts
        std::vector<bool> fPrimaryPhoton_; //true is photon is primary (not scattered)
        //Estimated values for hit points, ALWAYS CHECK CUTS PASSING BEFORE USING !!! (fails included)
        std::vector<double> fHitPhi_; //values of azimuthal angle for hit points
        std::vector<double> fHitTheta_;//values of polar angle for hit points
        std::vector<TLorentzVector> fHitPoint_; //x, y, z, t [mm and mikro s]
        std::vector<double> fEdep_; //deposited energy by gammas
        std::vector<double> fEdepSmear_; //deposited energy by gammas with experimental smearing
        typedef TObject inherited;


};
#endif
