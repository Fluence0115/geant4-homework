#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"

#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // materials
    auto nist = G4NistManager::Instance();
    auto matAir = nist->FindOrBuildMaterial("G4_AIR");
    auto matWater = nist->FindOrBuildMaterial("G4_WATER");
    auto matPolyethylene = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    // World
    auto worldSize = 5. * m;
    auto worldSol = new G4Box("World", .5 * worldSize, .5 * worldSize, .5 * worldSize);
    auto worldLog = new G4LogicalVolume(worldSol, matAir, "World");
    auto worldPhy = new G4PVPlacement(nullptr, G4ThreeVector(), worldLog, "World", nullptr, false, 0);

    // Polyethylene1
    auto Polyethylene1Pos = G4ThreeVector(150.*cm, 0., 0.*cm);
    auto Polyethylene1Xlength = 100. * cm;
    auto Polyethylene1Ylength = 200. * cm;
    auto Polyethylene1Zlength =  60. * cm;

    auto Polyethylene1Sol = new G4Box("Polyethylene1", .5 * Polyethylene1Xlength, .5 * Polyethylene1Ylength, .5 * Polyethylene1Zlength); // Solid : 지오메트리 모양, 크기
    auto Polyethylene1Log = new G4LogicalVolume(Polyethylene1Sol, matPolyethylene, "Polyethylene1"); // Logical : 지오메트리의 매질 등 질적인 특성에 대한 정보
    new G4PVPlacement(nullptr, Polyethylene1Pos, Polyethylene1Log, "Polyethylene1", worldLog, false, 0); // Physical : 지오메트리의 위치, 회전, 소속 등 배치에 대한 정보 담당

    // Polyethylene2
    auto Polyethylene2Pos = G4ThreeVector(212.54 *cm, 0.*cm, 0.*cm);
    auto Polyethylene2Xlength = 5.08 * cm;
    auto Polyethylene2Ylength = 15.24 * cm;
    auto Polyethylene2Zlength = 0.5 * cm;
    
    auto Polyethylene2Sol = new G4Box("Polyethylene2", .5 * Polyethylene2Xlength, .5 * Polyethylene2Ylength, .5 * Polyethylene2Zlength);
    auto Polyethylene2Log = new G4LogicalVolume(Polyethylene2Sol, matPolyethylene, "Polyethylene2");
    new G4PVPlacement(nullptr, Polyethylene2Pos, Polyethylene2Log, "Polyethylene2", worldLog, false, 0);
    
    return worldPhy;
    
}

void DetectorConstruction::ConstructSDandField()
{
    // MFD 등록
    auto mfd = new G4MultiFunctionalDetector("Detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(mfd);

    // PS 1 등록 -> 여러개의 PS를 등록할 때도 마찬가지로 사용하면 된다.
    auto psEDep = new G4PSEnergyDeposit("EDep"); 
    mfd->RegisterPrimitive(psEDep);
    
    /* 
    PS 2 등록 예시

    auto psDoseDep = new G4PSDoseDeposit("DoseDep"); 
    mfd->RegisterPrimitive(psDoseDep);
    */

    /*     
    Filter 세팅하기 : Filter는 PS의 추가옵션같은 기능 

    1) 원하는 PS 클래스의 객체를 만든다.
    2) 해당 Filter 객체를 PS에 세팅 
    3) 해당 PS 객체를 MFD에 등록    
    */ 

    // Logical Volume에 SD setting
    SetSensitiveDetector("Polyethylene1", mfd);
    SetSensitiveDetector("Polyethylene2", mfd);

    /*
    SetSensitiveDetector("shielding1", mfd);
    SetSensitiveDetector("shielding2", mfd);
    */
   }
