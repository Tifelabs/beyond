#include <iostream>
#include <string_view>
#include <fstream>
#include <vector>
#include <filesystem>

enum AirCraft {
    AIRBUS,
    BOEING,
    BOMBARDIER,
    CONCORDE,
    CESSNA,
    CRJ,
    DOUGLAS,
    EMBRAER,
    GULFSTREAM,
};

constexpr std::string_view fileNameFor(AirCraft model) {
    switch (model) {
        case AIRBUS:      return "AIRBUS.txt";
        case BOEING:      return "BOEING.txt";
        case BOMBARDIER:  return "BOMBARDIER.txt";
        case CONCORDE:    return "CONCORDE.txt";
        case CESSNA:      return "CESSNA.txt";
        case CRJ:         return "CRJ.txt";
        case DOUGLAS:     return "DOUGLAS.txt";
        case EMBRAER:     return "EMBRAER.txt";
        case GULFSTREAM:  return "GULFSTREAM.txt";
        default:          return "UNKNOWN.txt";
    }
}

std::vector<std::string_view> modelsFor(AirCraft model) {
    switch (model) {
        case AIRBUS:
            return {"A300", "A310", "A318", "A319", "A320", "A321",
                     "A330", "A340", "A350", "A380", "A220"};
        case BOEING:
            return {"707", "717", "727", "737", "747", "757", "767",
                     "777", "787 Dreamliner"};
        case BOMBARDIER:
            return {"CRJ100", "CRJ200", "CRJ700", "CRJ900", "CRJ1000",
                     "Dash 8 / Q400", "Global Express", "Challenger 300",
                     "Challenger 600", "Learjet 75"};
        case CONCORDE:
            return {"Concorde 001", "Concorde 002", "Concorde 101", "Concorde 102"};
        case CESSNA:
            return {"150", "152", "172 Skyhawk", "182 Skylane", "206 Stationair",
                     "208 Caravan", "210 Centurion", "Citation Mustang",
                     "Citation CJ", "Citation X", "Citation Longitude"};
        case CRJ:
            return {"CRJ100", "CRJ200", "CRJ440", "CRJ700", "CRJ701",
                     "CRJ702", "CRJ705", "CRJ900", "CRJ1000"};
        case DOUGLAS:
            return {"DC-1", "DC-2", "DC-3", "DC-4", "DC-5", "DC-6", "DC-7",
                     "DC-8", "DC-9", "DC-10", "MD-11", "MD-80", "MD-90"};
        case EMBRAER:
            return {"EMB 110 Bandeirante", "EMB 120 Brasilia", "ERJ 145",
                     "E170", "E175", "E190", "E195", "E190-E2", "E195-E2",
                     "Phenom 100", "Phenom 300", "Legacy 500", "Praetor 600"};
        case GULFSTREAM:
            return {"Gulfstream I", "Gulfstream II", "Gulfstream III",
                     "Gulfstream IV", "Gulfstream V", "G280", "G450",
                     "G550", "G600", "G650", "G700", "G800"};
        default:
            return {};
    }
}

bool writeModelFile(AirCraft model, const std::filesystem::path& outDir) {
    std::filesystem::path path = outDir / fileNameFor(model);

    std::ofstream ouf(path); 
    if (!ouf) {
        std::cerr << "Error opening [ " << path << " ]\n";
        return false;
    }

    for (std::string_view name : modelsFor(model)) {
        ouf << name << '\n';
    }

    return true; 
}

int main() {
    const std::filesystem::path outDir = "aircraft";
    std::filesystem::create_directories(outDir);

    const AirCraft all[] = {
        AIRBUS, BOEING, BOMBARDIER, CONCORDE, CESSNA,
        CRJ, DOUGLAS, EMBRAER, GULFSTREAM
    };

    int failures = 0;
    for (AirCraft model : all) {
        if (!writeModelFile(model, outDir)) {
            ++failures;
        }
    }

    if (failures > 0) {
        std::cerr << failures << " file(s) failed to write.\n";
        return 1;
    }

    std::cout << "Wrote " << (sizeof(all) / sizeof(all[0])) << " files to \"" << outDir.string() << "\"\n";
    return 0;
}