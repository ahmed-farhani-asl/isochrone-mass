#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main() {
    // Declare variables for total mass, remaining mass, and other intermediate values
    double m_tot = 0, m_rem = 0, mi, mlive, m, age, tempAge, tempM, dm = 0.1, trash;
    double *iniMass, **Mass, **M_Live, *Age; // Arrays to store initial mass, mass, live mass, and age data
    int a = 0, b = 0, time_steps, num, num_1st, *num_age; // Counters and variables for time steps and data size
    char ch;
    bool s = true;
    string line;
    ofstream write("Mini_Mlive.dat"), write2; // Output files for processed data
    ifstream scan("isochrone.dat"), scan2; // Input file for isochrone data

    // Skip the first 12 lines of the input file (header information)
    while (getline(scan, line)) {
        a++;
        if (a == 12) break;
    }
    a = 0;

    // Write the header for the output file
    write << "LogAge" << "\t\t" << "ini_mass" << "\t\t" << "Live_mass" << endl;

    // Read the isochrone data and filter out masses greater than 150
    while (scan >> trash >> trash >> age >> mi >> trash >> mlive) {
        if (mi > 150) {
            getline(scan, line);
            scan >> ch;
            if (ch == '#') {
                getline(scan, line);
                b++;
            }
            continue;
        }

        // Write the filtered data to the output file
        write << age << "\t\t" << mi << "\t\t" << mlive << endl;

        getline(scan, line);
        scan >> ch;
        if (ch == '#') {
            getline(scan, line);
            b++;
        }
    }

    // Allocate memory for arrays based on the number of time steps
    num_age = new int[b];
    Mass = new double*[b];
    M_Live = new double*[b];
    Age = new double[b];
    time_steps = b;
    b = 0;

    // Close and reopen the output file for reading
    scan.close();
    write.close();
    scan.open("Mini_Mlive.dat");

    // Read the processed data and organize it into arrays
    getline(scan, line);
    while (scan >> age >> mi >> mlive) {
        if (s == true) {
            tempAge = age;
            s = false;
        }

        if (age > tempAge) {
            Mass[b] = new double[a];
            M_Live[b] = new double[a];
            num_age[b] = a;

            if (b == 0) {
                iniMass = new double[a];
                num_1st = a;
            }
            a = 0;
            b++;
        }

        a++;
        tempAge = age;
    }

    // Allocate memory for the last time step
    Mass[b] = new double[a];
    M_Live[b] = new double[a];
    num_age[b] = a;

    // Close and reopen the output file for reading
    scan.close();
    scan.open("Mini_Mlive.dat");

    // Reset counters and read the data into the allocated arrays
    a = 0;
    b = 0;
    s = true;

    getline(scan, line);
    while (scan >> age >> mi >> mlive) {
        if (s == true) {
            tempAge = age;
            Age[0] = age;
            s = false;
        }

        if (age > tempAge) {
            a = 0;
            b++;
            Age[b] = age;
        }

        Mass[b][a] = mi;
        M_Live[b][a] = mlive;
        if (b == 0) iniMass[a] = mi;
        a++;
        tempAge = age;
    }
    scan.close();

    // Open output files for total mass and total mass + remnants
    write.open("totalMass.dat");
    write2.open("totalMass+ Remnants.dat");

    // Calculate the total mass and remnants for each time step
    for (int i = 0; i < time_steps; i++) {
        scan.open("imf N = 100000.dat");
        while (scan >> m >> num) {
            for (int j = 0; j < num_age[i]; j++) {
                if ((Mass[i][j] - m) < dm * m) m_tot += M_Live[i][j] * num;
                tempM = Mass[i][j];
            }

            if (tempM < m) {
                for (int k = 0; k < num_1st; k++) {
                    if ((iniMass[k] - m) < dm * m && iniMass[k] > tempM) {
                        if (iniMass[k] < 8.5 && iniMass[k] >= 0.85) m_rem += (0.077 * iniMass[k] + 0.48) * num;
                        if (iniMass[k] < 40 && iniMass[k] >= 8.5) m_rem += 1.4 * num;
                        if (iniMass[k] >= 40) m_rem += 0.5 * iniMass[k] * num;
                    }
                }
            }
        }
        scan.close();

        // Write the results to the output files
        write << Age[i] << "\t\t" << m_tot << endl;
        write2 << Age[i] << "\t\t" << m_tot + m_rem << endl;
        m_tot = 0;
        m_rem = 0;
    }
}