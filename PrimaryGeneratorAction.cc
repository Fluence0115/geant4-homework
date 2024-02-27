#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    fPrimary->SetParticleDefinition(G4Neutron::Definition());
    fPrimary->SetParticleEnergy(2.2*MeV);
    fPrimary->SetParticlePosition(G4ThreeVector());
    fPrimary->SetParticleMomentumDirection(G4RandomDirection());
    
    fPrimary->GeneratePrimaryVertex(anEvent);
}
