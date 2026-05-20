
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// 1. DATA STRUCTURES & EXCEPTIONS

struct Load {
    string name;
    double powerDemand;
    int priority;
    bool isConnected;

    static bool comparePriority(const Load& a, const Load& b) {
        return a.priority > b.priority;
    }

    string serialize() const {
        return name + "," + to_string(powerDemand) + "," + to_string(priority) + "," + (isConnected ? "1" : "0");
    }
};

class InsufficientPowerException : public runtime_error {
    public:
        InsufficientPowerException(const string& message) : runtime_error(message) {}
};

// 2. BASE & DERIVED CLASSES (DOMAIN LOGIC)

class PowerSource {
    protected:
        string assetId;
        bool isOnline;
    public:
        PowerSource(string id) : assetId(id), isOnline(true) {}
        virtual ~PowerSource() = default;

        virtual double calculatePower(double envFactor1, double envFactor2) = 0;
        virtual string getType() const = 0;
        virtual string serialize() const = 0;

        string getId() const { return assetId; }
        bool getStatus() const { return isOnline; }
        void toggleStatus() { isOnline = !isOnline; }
};

class SolarArray : public PowerSource {
    private:
        double P_max;
        double G_std = 1000.0;
        double alpha;
    public:
        SolarArray(string id, double pMax, double tempCoef)
            : PowerSource(id), P_max(pMax), alpha(tempCoef) {}

        double calculatePower(double irradiance, double temp) override {
            if (!isOnline) return 0.0;
            double output = P_max * (irradiance / G_std) * (1 + alpha * (temp - 25.0));
            return (output > 0) ? output : 0;
        }
        string getType() const override { return "Solar Array"; }
        string serialize() const override {
            return "Solar," + assetId + "," + to_string(P_max) + "," + to_string(alpha);
        }
};

class WindTurbine : public PowerSource {
    private:
        double efficiency;
        double rotorArea;
        double airDensity = 1.225;
    public:
        WindTurbine(string id, double eff, double area)
            : PowerSource(id), efficiency(eff), rotorArea(area) {}

        double calculatePower(double windSpeed, double dummyVar) override {
            if (!isOnline) return 0.0;
            if (windSpeed > 25.0) return 0.0;
            return 0.5 * airDensity * rotorArea * pow(windSpeed, 3) * efficiency / 1000.0;
        }
        string getType() const override { return "Wind Turbine"; }
        string serialize() const override {
            return "Wind," + assetId + "," + to_string(efficiency) + "," + to_string(rotorArea);
        }
};

// 3. ENCAPSULATED CLASSES
class Battery {
    private:
        double capacity;
        double chargeLevel;
    public:
        Battery(double cap) : capacity(cap), chargeLevel(cap * 0.8) {}

        double discharge(double requestedPower) {
            if (chargeLevel >= requestedPower) {
                chargeLevel -= requestedPower;
                return requestedPower;
            } else {
                double provided = chargeLevel;
                chargeLevel = 0;
                return provided;
            }
        }

        void charge(double excessPower) {
            chargeLevel = min(capacity, chargeLevel + excessPower);
        }

        double getLevel() const { return chargeLevel; }
        double getCapacity() const { return capacity; }
};

// 4. MICROGRID CONTROLLER

class ControlCenter {
private:
    vector<PowerSource*> gridAssets;
    vector<Load> registeredLoads;
    Battery gridBattery;
    string assetDataFile = "energy_assets.csv";
    string loadDataFile = "consumer_loads.csv";

public:
    ControlCenter(double batteryCap) : gridBattery(batteryCap) {
        loadAssetsFromFile();
        loadLoadsFromFile();
    }

    ~ControlCenter() {
        for (auto asset : gridAssets) delete asset;
    }

    // --- Asset Management ---
    vector<PowerSource*>& getAssets() { return gridAssets; }

    void addAsset(PowerSource* asset) {
        gridAssets.push_back(asset);
        saveAssetsToFile();
    }

    void removeAsset(int index) {
        if (index >= 0 && index < gridAssets.size()) {
            delete gridAssets[index];
            gridAssets.erase(gridAssets.begin() + index);
            saveAssetsToFile();
        }
    }

    void toggleAsset(int index) {
        if (index >= 0 && index < gridAssets.size()) {
            gridAssets[index]->toggleStatus();
        }
    }

    void saveAssetsToFile() {
        ofstream outFile(assetDataFile);
        if (outFile.is_open()) {
            for (const auto& asset : gridAssets) {
                outFile << asset->serialize() << "\n";
            }
            outFile.close();
        }
    }

    void loadAssetsFromFile() {
        ifstream inFile(assetDataFile);
        string line, type, id, param1, param2;
        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                getline(ss, type, ',');
                getline(ss, id, ',');
                getline(ss, param1, ',');
                getline(ss, param2, ',');

                if (type == "Solar") {
                    gridAssets.push_back(new SolarArray(id, stod(param1), stod(param2)));
                } else if (type == "Wind") {
                    gridAssets.push_back(new WindTurbine(id, stod(param1), stod(param2)));
                }
            }
            inFile.close();
        }
    }

    // --- Load Management ---
    vector<Load>& getLoads() { return registeredLoads; }

    void addLoad(const Load& load) {
        registeredLoads.push_back(load);
        saveLoadsToFile();
    }

    void removeLoad(int index) {
        if (index >= 0 && index < registeredLoads.size()) {
            registeredLoads.erase(registeredLoads.begin() + index);
            saveLoadsToFile();
        }
    }

    void toggleLoad(int index) {
        if (index >= 0 && index < registeredLoads.size()) {
            registeredLoads[index].isConnected = !registeredLoads[index].isConnected;
            saveLoadsToFile();
        }
    }

    void saveLoadsToFile() {
        ofstream outFile(loadDataFile);
        if (outFile.is_open()) {
            for (const auto& load : registeredLoads) {
                outFile << load.serialize() << "\n";
            }
            outFile.close();
        }
    }

    void loadLoadsFromFile() {
        ifstream inFile(loadDataFile);
        string line, name, demandStr, priorityStr, connectedStr;
        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                getline(ss, name, ',');
                getline(ss, demandStr, ',');
                getline(ss, priorityStr, ',');
                getline(ss, connectedStr, ',');

                if(!name.empty()) {
                    registeredLoads.push_back({
                        name,
                        stod(demandStr),
                        stoi(priorityStr),
                        connectedStr == "1"
                    });
                }
            }
            inFile.close();
        }
    }

    // --- Simulation & Dashboards ---
    void printDashboard() {
        cout << "\n===================================================================\n";
        cout << "                       MICROGRID DASHBOARD                         \n";
        cout << "===================================================================\n";
        cout << "BATTERY STATUS: " << fixed << setprecision(2) << gridBattery.getLevel()
             << " / " << gridBattery.getCapacity() << " kWh\n";
        cout << "-------------------------------------------------------------------\n";
        cout << left << setw(15) << "ASSET ID" << setw(20) << "TYPE" << setw(10) << "STATUS" << "\n";
        cout << "-------------------------------------------------------------------\n";
        if (gridAssets.empty()) cout << "No energy assets deployed.\n";
        for (const auto& asset : gridAssets) {
            cout << left << setw(15) << asset->getId()
                 << setw(20) << asset->getType()
                 << (asset->getStatus() ? "[ONLINE]" : "[OFFLINE]") << "\n";
        }
        cout << "===================================================================\n";
    }

    void simulateStep(double irradiance, double temp, double windSpeed) {
        double totalGenerated = 0;
        for (auto asset : gridAssets) {
            totalGenerated += asset->calculatePower(irradiance, temp) +
                              asset->calculatePower(windSpeed, 0);
        }

        double totalDemand = 0;
        for (const auto& load : registeredLoads) {
            if (load.isConnected) totalDemand += load.powerDemand;
        }

        cout << "\n--- Step Results ---\n";
        cout << "Total Generation: " << totalGenerated << " kW\n";
        cout << "Total Demand:     " << totalDemand << " kW\n";

        try {
            if (totalDemand > totalGenerated) {
                double deficit = totalDemand - totalGenerated;
                double batteryContribution = gridBattery.discharge(deficit);
                totalGenerated += batteryContribution;

                if (totalDemand > totalGenerated) {
                    throw InsufficientPowerException("CRITICAL: Demand exceeds Generation + Storage.");
                } else {
                    cout << "[SYS] Grid Balanced: Battery supplied " << batteryContribution << " kW.\n";
                }
            } else {
                double excess = totalGenerated - totalDemand;
                gridBattery.charge(excess);
                cout << "[SYS] Grid Balanced: Excess " << excess << " kW sent to Battery.\n";
            }
        } catch (const InsufficientPowerException& e) {
            cout << "\n[!] EXCEPTION CAUGHT: " << e.what() << "\n";
            triggerLoadShedding(totalGenerated);
        }
    }

private:
    void triggerLoadShedding(double availablePower) {
        cout << "--- Initiating Load Shedding Algorithm ---\n";
        sort(registeredLoads.begin(), registeredLoads.end(), Load::comparePriority);

        for (auto& current : registeredLoads) {
            if (!current.isConnected) continue;

            if (availablePower >= current.powerDemand) {
                availablePower -= current.powerDemand;
                cout << "[SUPPLIED] " << current.name << " (Priority " << current.priority << ")\n";
            } else {
                current.isConnected = false;
                cout << "[SHEDDING] " << current.name << " disconnected to save grid.\n";
            }
        }
        saveLoadsToFile(); 
    }
};

// 5. APPLICATION UI & SESSION MANAGEMENT

class Application {
private:
    ControlCenter* grid;
    string currentUser;
    bool isLoggedIn;

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double getValidatedInput(const string& prompt, double minVal, double maxVal) {
        double val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= minVal && val <= maxVal) {
                return val;
            }
            clearInputBuffer();
            cout << "[Error] Please enter a value between " << minVal << " and " << maxVal << ".\n";
        }
    }

public:
    Application() {
        grid = new ControlCenter(1000.0);
        isLoggedIn = false;
    }

    ~Application() { delete grid; }

    void start() {
        cout << "======================================\n";
        cout << " DECENTRALIZED MICROGRID OS v3.0 \n";
        cout << "======================================\n";

        while (!isLoggedIn) {
            cout << "Enter Operator ID (Hint: admin): ";
            getline(cin, currentUser);
            if (currentUser == "admin") {
                isLoggedIn = true;
                cout << "Login successful. Welcome, Operator.\n";
            } else {
                cout << "Access Denied.\n";
            }
        }
        mainMenu();
    }

private:
    void mainMenu() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n--- MAIN MENU ---\n";
            cout << "1. View Grid Dashboard\n";
            cout << "2. Manage Energy Assets\n";
            cout << "3. Manage Consumer Loads\n";
            cout << "4. Run Manual Simulation Step\n";
            cout << "0. Logout & Exit\n";
            cout << "Select option: ";

            if (!(cin >> choice)) {
                clearInputBuffer();
                cout << "Invalid input.\n";
                continue;
            }

            switch(choice) {
                case 1: grid->printDashboard(); break;
                case 2: uiManageAssets(); break;
                case 3: uiManageLoads(); break;
                case 4: uiRunStep(); break;
                case 0: cout << "Logging out...\n"; break;
                default: cout << "Invalid option.\n";
            }
        }
    }

    void uiManageAssets() {
        int choice = -1;
        while (choice != 0) {
            auto& assets = grid->getAssets();
            cout << "\n--- Energy Asset Management ---\n";
            cout << left << setw(5) << "IDX" << setw(15) << "ASSET ID" << setw(20) << "TYPE"
                 << setw(10) << "STATUS" << "\n";
            cout << "-------------------------------------------------------------------\n";
            if (assets.empty()) cout << "No assets registered.\n";
            for (size_t i = 0; i < assets.size(); ++i) {
                cout << left << setw(5) << i << setw(15) << assets[i]->getId()
                     << setw(20) << assets[i]->getType()
                     << (assets[i]->getStatus() ? "[ONLINE]" : "[OFFLINE]") << "\n";
            }
            cout << "\n1. Add New Asset\n2. Remove Asset\n3. Toggle Asset (Online/Offline)\n0. Back\nSelect: ";
            cin >> choice;

            if (choice == 1) {
                int type = getValidatedInput("\n1. Solar Array\n2. Wind Turbine\nSelect Type: ", 1, 2);
                string id;
                cout << "Enter Asset ID (e.g., PV-01): ";
                cin >> id;

                if (type == 1) {
                    double pMax = getValidatedInput("Enter Max Power kW (Typical 10-500): ", 1.0, 5000.0);
                    double tempCoef = getValidatedInput("Enter Temp Coefficient (Typical -0.005 to -0.003): ", -0.01, 0.0);
                    grid->addAsset(new SolarArray(id, pMax, tempCoef));
                    cout << "[SUCCESS] Solar Array added and saved to disk.\n";
                } else if (type == 2) {
                    double eff = getValidatedInput("Enter Efficiency (Typical 0.2 - 0.45): ", 0.01, 0.59);
                    double area = getValidatedInput("Enter Rotor Area m^2 (Typical 10-1000): ", 1.0, 5000.0);
                    grid->addAsset(new WindTurbine(id, eff, area));
                    cout << "[SUCCESS] Wind Turbine added and saved to disk.\n";
                }
            }
            else if (choice == 2 && !assets.empty()) {
                int idx = getValidatedInput("Enter Index of Asset to Remove: ", 0, assets.size() - 1);
                grid->removeAsset(idx);
                cout << "[SUCCESS] Asset removed from grid and disk.\n";
            }
            else if (choice == 3 && !assets.empty()) {
                int idx = getValidatedInput("Enter Index of Asset to Toggle: ", 0, assets.size() - 1);
                grid->toggleAsset(idx);
                cout << "[SUCCESS] Asset operational status toggled.\n";
            }
        }
    }

    void uiManageLoads() {
        int choice = -1;
        while (choice != 0) {
            auto& loads = grid->getLoads();
            cout << "\n--- Load Management ---\n";
            cout << left << setw(5) << "IDX" << setw(20) << "NAME" << setw(10) << "DEMAND"
                 << setw(10) << "PRIORITY" << setw(10) << "STATUS" << "\n";
            cout << "---------------------------------------------------------\n";
            if (loads.empty()) cout << "No loads registered.\n";
            for (size_t i = 0; i < loads.size(); ++i) {
                cout << left << setw(5) << i << setw(20) << loads[i].name
                     << loads[i].powerDemand << " kW     " << setw(10) << loads[i].priority
                     << (loads[i].isConnected ? "[ON]" : "[OFF]") << "\n";
            }
            cout << "\n1. Add New Load\n2. Remove Load\n3. Toggle Load Power\n0. Back\nSelect: ";
            cin >> choice;

            if (choice == 1) {
                string name;
                clearInputBuffer();
                cout << "Enter Load Name: ";
                getline(cin, name);
                double demand = getValidatedInput("Enter Power Demand kW: ", 0.1, 5000.0);
                int priority = getValidatedInput("Enter Priority (1 = Lowest, 10 = Critical): ", 1, 10);
                grid->addLoad({name, demand, priority, true});
                cout << "[SUCCESS] Load added and saved to disk.\n"; // Updated message
            }
            else if (choice == 2 && !loads.empty()) {
                int idx = getValidatedInput("Enter Index of Load to Remove: ", 0, loads.size() - 1);
                grid->removeLoad(idx);
                cout << "[SUCCESS] Load removed from grid and disk.\n"; // Updated message
            }
            else if (choice == 3 && !loads.empty()) {
                int idx = getValidatedInput("Enter Index of Load to Toggle: ", 0, loads.size() - 1);
                grid->toggleLoad(idx);
                cout << "[SUCCESS] Load status toggled and saved.\n"; // Updated message
            }
        }
    }

    void uiRunStep() {
        cout << "\n--- Manual Environmental Input ---\n";
        double irradiance = getValidatedInput("Enter Solar Irradiance W/m^2 (Typical: 0 [Night] - 1000 [Clear Noon]): ", 0.0, 1200.0);
        double temp = getValidatedInput("Enter Ambient Temperature C (Typical: 10 - 40): ", -20.0, 60.0);
        double windSpeed = getValidatedInput("Enter Wind Speed m/s (Typical: 0 [Calm] - 15 [Strong]): ", 0.0, 35.0);

        grid->simulateStep(irradiance, temp, windSpeed);
    }
};

// 6. MAIN ENTRY POINT

int main() {
    Application app;
    app.start();
    return 0;
}

