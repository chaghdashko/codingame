#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <cstdio>

using namespace std;

class Defib {
private:
    string name;
    double latitude;
    double longitude;
    
public: 
    Defib(const string& _name, const double& _lat, const double& _lon)
        : name(_name), latitude(_lat), longitude(_lon) 
    {}
    
    double get_lat() const {
        return latitude;
    }
    
    double get_lon() const {
        return longitude;
    }
    
    string get_name() const {
        return name;
    }
};

static double get_distance(const double& a_lat, const double& b_lat, const double& a_lon, const double& b_lon) {
    double dist_x = (a_lon - b_lon) * cos((a_lat + b_lat) / 2);
    double dist_y = a_lat - b_lat;
    double dist = sqrt((dist_x * dist_x) + (dist_y * dist_y)) * 6371;
    
    return dist;
}

static double read_patient_longitude() {
    string LON;
    cin >> LON; cin.ignore();
    size_t p = LON.find_first_of(",");
    double patient_longitude = stod(LON.replace(p, 1, "."));
    
    return patient_longitude * M_PI/180;
}

static double read_patient_latitude() {
    string LAT;
    cin >> LAT; cin.ignore();
    size_t p = LAT.find_first_of(",");
    double patient_latitude = stod(LAT.replace(p, 1, "."));
    
    return patient_latitude * M_PI/180;
}

static vector<Defib> read_defib_data() {
    int N;
    cin >> N; cin.ignore();
    
    vector<Defib> defibs;
    
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        
        // Skip index
        string search_str = ";";
        size_t pos = DEFIB.find_first_of(search_str);
        DEFIB = DEFIB.substr(pos + 1);
        
        // parse name
        pos = DEFIB.find_first_of(search_str);
        string name = DEFIB.substr(0, pos);
        
        // skip address
        DEFIB = DEFIB.substr(pos + 1);
        pos = DEFIB.find_first_of(search_str);
        
        // skip phone
        DEFIB = DEFIB.substr(pos + 1);
        pos = DEFIB.find_first_of(search_str);
        DEFIB = DEFIB.substr(pos + 1);
        
        pos = DEFIB.find_first_of(search_str);
        string lon_str = DEFIB.substr(0, pos);
        size_t pos2 = lon_str.find_first_of(",");
        lon_str.replace(pos2, 1, ".");
        
        string lat_str = DEFIB.substr(pos + 1);
        pos2 = lat_str.find_first_of(",");
        lat_str.replace(pos2, 1, ".");
        
        Defib defib(name, stod(lat_str) * M_PI/180, stod(lon_str) * M_PI/180);
        
        defibs.emplace_back(defib);
    }
    
    return defibs;
}

static Defib calc_nearest_defib(const vector<Defib>& defibs, const double& patient_latitude, const double& patient_longitude) {
    Defib min = defibs[0];
    double dist_min = get_distance(patient_latitude, defibs[0].get_lat(), patient_longitude, defibs[0].get_lon());
    //printf("%.20f :: %s\n\n", dist_min, defibs[0].get_name().c_str());
    
    for (vector<Defib>::const_iterator it = defibs.begin(); it != defibs.end(); ++it) {
        double dist = get_distance(patient_latitude, it->get_lat(), patient_longitude, it->get_lon());
        //printf("Current: %.20f :: %s\n", dist, it->get_name().c_str());
        if (dist < dist_min) {
            dist_min = dist;
            min = *it;
        }
        //printf("    Min: %.20f :: %s\n\n", dist_min, min.get_name().c_str());
    }
    
    return min;
}

int main() {
    double patient_longitude = read_patient_longitude();
    double patient_latitude = read_patient_latitude();
    vector<Defib> defibs = read_defib_data();
    Defib min = calc_nearest_defib(defibs, patient_latitude, patient_longitude);
    cout << min.get_name() << endl;
}
