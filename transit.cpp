#include <iostream>
#include <string>
#include <vector>

enum TransitType {
    BUS,
    RAIL
};

struct Stop {
    std::string id;
    std::string name;
    std::string zone;
    TransitType type;
};

struct Route {
    std::string id;
    std::string name;
    TransitType type;
    std::vector<Stop> stops;
}; 

namespace Coordinate {

    const std::vector<std::pair<std::string, std::string>> zone_map = {
        {"NR", "NORTH"},
        {"ET", "EAST"},    
        {"NE", "NORTH EAST"},
        {"NW", "NORTH WEST"}, 
        {"WT", "WEST"},
        {"ST", "SOUTH"},
        {"SE", "SOUTH EAST"},
        {"SW", "SOUTH WEST"},
    };

    std::string expand_zone(const std::string& code) {
        for (const auto& pair : zone_map) {
            if (pair.first == code) return pair.second;
        }
        return "UNKNOWN";
    }

    std::string get_cord() {
        std::string cord;
        std::cin >> cord;
        return expand_zone(cord);
    }

}
class TransitSystem {
    std::vector<Route> routes;

public:

    void add_route(const Route& r) {
        routes.push_back(r);
    }

    void remove_route(const std::string& route_id) {
        for (auto it = routes.begin(); it != routes.end(); ++it) {
            if (it->id == route_id) {
                routes.erase(it);
                std::cout << "Route " << route_id << " removed.\n";
                return;
            }
        }
        std::cout << "Route " << route_id << " not found.\n";
    }

    void add_stop_to_route(const std::string& route_id, const Stop& s) {
        for (auto& route : routes) {
            if (route.id == route_id) {
                route.stops.push_back(s);
                std::cout << "Stop " << s.name << " added to route " << route_id << ".\n";
                return;
            }
        }
        std::cout << "Route " << route_id << " not found.\n";
    }

    // Remove a stop from a route
    void remove_stop(const std::string& route_id, const std::string& stop_id) {
        for (auto& route : routes) {
            if (route.id == route_id) {
                for (auto it = route.stops.begin(); it != route.stops.end(); ++it) {
                    if (it->id == stop_id) {
                        route.stops.erase(it);
                        std::cout << "Stop " << stop_id << " removed.\n";
                        return;
                    }
                }
                std::cout << "Stop " << stop_id << " not found in route " << route_id << ".\n";
                return;
            }
        }
        std::cout << "Route " << route_id << " not found.\n";
    }

    void display_route(const std::string& route_id) const {
        for (const auto& route : routes) {
            if (route.id == route_id) {
                std::cout << "[" << (route.type == BUS ? "BUS" : "RAIL") << "] "
                          << route.name << " (" << route.id << ")\n";
                for (size_t i = 0; i < route.stops.size(); ++i) {
                    const Stop& s = route.stops[i];
                    std::cout << "  " << i + 1 << ". "
                              << s.name << " [" << s.id << "] "
                              << "Zone: " << Coordinate::expand_zone(s.zone) << "\n";
                }
                return;
            }
        }
        std::cout << "Route " << route_id << " not found.\n";
    }

    void display_all() const {
        if (routes.empty()) {
            std::cout << "No routes in system.\n";
            return;
        }
        for (const auto& route : routes) {
            display_route(route.id);
            std::cout << "\n";
        }
    }
};

void print_menu() {
    std::cout << "\n=== Transit System ===\n"
              << "1. Add route\n"
              << "2. Remove route\n"
              << "3. Add stop to route\n"
              << "4. Remove stop from route\n"
              << "5. Display route\n"
              << "6. Display all routes\n"
              << "0. Exit\n"
              << "Choice: ";
}

TransitType parse_type(const std::string& t) {
    return (t == "BUS" || t == "bus") ? BUS : RAIL;
}

int main() {
    TransitSystem system;
    int choice;

    while (true) {
        print_menu();
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            Route r;
            std::string type;
            std::cout << "Route ID: ";    std::cin >> r.id;
            std::cout << "Route name: ";  std::cin >> r.name;
            std::cout << "Type (BUS/RAIL): "; std::cin >> type;
            r.type = parse_type(type);
            system.add_route(r);
            std::cout << "Route added.\n";

        } else if (choice == 2) {
            std::string id;
            std::cout << "Route ID to remove: "; std::cin >> id;
            system.remove_route(id);

        } else if (choice == 3) {
            std::string route_id;
            Stop s;
            std::string type;
            std::cout << "Route ID: ";    std::cin >> route_id;
            std::cout << "Stop ID: ";     std::cin >> s.id;
            std::cout << "Stop name: ";   std::cin >> s.name;
            std::cout << "Zone code (e.g. NR, ST, NE): "; std::cin >> s.zone;
            std::cout << "Type (BUS/RAIL): "; std::cin >> type;
            s.type = parse_type(type);
            system.add_stop_to_route(route_id, s);

        } else if (choice == 4) {
            std::string route_id, stop_id;
            std::cout << "Route ID: "; std::cin >> route_id;
            std::cout << "Stop ID: ";  std::cin >> stop_id;
            system.remove_stop(route_id, stop_id);

        } else if (choice == 5) {
            std::string id;
            std::cout << "Route ID: "; std::cin >> id;
            system.display_route(id);

        } else if (choice == 6) {
            system.display_all();

        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Exiting.\n";
    return 0;
}