#include <stdio.h>
#include <math.h>

/* Δείκτες για τον πίνακα των συντελεστών */
#define INDEX_AGE 0
#define INDEX_TC 1
#define INDEX_HDL 2
#define INDEX_SBP_NO_TREATMENT 3
#define INDEX_SBP_TREATMENT 4
#define INDEX_SMOKING 5
#define INDEX_DIABETES 6

/*
    Σε όλους τους πίνακες η τιμή δείκτη 0 αφορά τους ΑΝΔΡΕΣ ενώ 1 τις ΓΥΝΑΙΚΕΣ.
 */
// ΖΗΤΟΥΜΕΝΟ α) πίνακας με τα SUM_REFERENCES, COEFFICIENTS, S0,
/* Πίνακας με τα μηνύματα προς τον χρήστη */
char *PROMPTS[] = {
    "Φύλο (0=Άνδρας, 1=Γυναίκα):",
    "Ηλικία 18-110:",
    "Ολική χοληστερόλη (mg/dL) 100-400:",
    "HDL χοληστερόλη (mg/dL) 20-110:",
    "Συστολική πίεση (mmHg) 60-220:",
    "Υπό αγωγή για υπέρταση; (0=Όχι, 1=Ναι):",
    "Καπνιστής; (0=Όχι, 1=Ναι):",
    "Σακχαρώδης διαβήτης; (0=Όχι, 1=Ναι):"};


// ΖΗΤΟΥΜΕΝΟ α) Πίνακες με σταθερές (δεδομένα από την εκφώνηση) 
double COEFFICIENTS[7][2] = {
    {3.06117, 2.3288},   // AGE
    {1.12370, 1.20904},   // TC
    {-0.93263, -0.70833}, // HDL
    {1.93303, 2.76157},   // Χωρίς αγωγή
    {1.99881, 2.82263},   // Με αγωγή
    {0.65451, 0.52873},   // SMOKING
    {0.57309, 0.69154}    // DIABETES
};

/* Μέσους όρους του αθροίσματος των βαρών (βX) */
double SUM_BETA_REFERENCES[2] = {23.9802, 26.1931};
double S0[2] = {0.88936, 0.95012};
double RANGES[8][2] = {
    {0, 1}, 
    {18, 110},
    {100, 400},
    {20, 110},
    {60, 220},
    {0, 1},  
    {0, 1},  
    {0, 1}
}; 

// ΖΗΤΟΥΜΕΝΟ β) Structure Patient
typedef struct{
    int sex;
    int age;
    int tc;
    int hdl;
    int sbp;
    int sbptreated;
    int smoker;
    int diabetes;
} Patient;



/* Δήλωση συναρτήσεων */
double framingham_risk_10y(Patient patient);
void risk_category(double risk);


 int main()
{
    float values[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    Patient p;
    int i;

    // ΖΗΤΟΥΜΕΝΟ γ) αμυντικός μηχανισμός για εισαγωγή τιμών και ανάθεση τιμών στο p
        for (i = 0; i < 8; i++) {
        do {
            printf("%s ", PROMPTS[i]);
            scanf("%f", &values[i]);
            if (values[i] < RANGES[i][0] || values[i] > RANGES[i][1])
                printf("Λάθος τιμή! Παρακαλώ εισάγετε τιμή μεταξύ %.0f και %.0f.\n", RANGES[i][0], RANGES[i][1]);
        } while (values[i] < RANGES[i][0] || values[i] > RANGES[i][1]);
    }

        // Ανάθεση τιμών στο struct p
    p.sex = (int)values[0];
    p.age = (int)values[1];
    p.tc = (int)values[2];
    p.hdl = (int)values[3];
    p.sbp = (int)values[4];
    p.sbptreated = (int)values[5];
    p.smoker = (int)values[6];
    p.diabetes = (int)values[7];

    double risk = framingham_risk_10y(p);
    printf("\n\t*****\tΑποτελέσματα\t*****\n");
    printf("Εκτιμώμενος 10ετής καρδιαγγειακός κίνδυνος:%.1lf%%\n", risk * 100);
    risk_category(risk);
    
    return 0;
}

/* ΖΗΤΟΥΜΕΝΟ δ) υλοποίηση συνάρτησης
   Η συνάρτηση που υπολογίζει το ρίσκο και το επιστρέφει*/
double framingham_risk_10y(Patient patient){
    int g = patient.sex;
    double sum_beta_x = 0;

    sum_beta_x += COEFFICIENTS[INDEX_AGE][g] * log(patient.age);
    sum_beta_x += COEFFICIENTS[INDEX_TC][g] * log(patient.tc);
    sum_beta_x += COEFFICIENTS[INDEX_HDL][g] * log(patient.hdl);
    

    //Όταν τα παρακάτων ΑΝ γίνουν αληθές.
    if (patient.sbptreated){
        sum_beta_x += COEFFICIENTS[INDEX_SBP_TREATMENT][g] * log(patient.sbp);
    }else{
        sum_beta_x += COEFFICIENTS[INDEX_SBP_NO_TREATMENT][g] * log(patient.sbp);
    }
    if (patient.smoker){
         sum_beta_x += COEFFICIENTS[INDEX_SMOKING][g];
    }
    if (patient.diabetes){
        sum_beta_x += COEFFICIENTS[INDEX_DIABETES][g];
    }

    return 1.0 - pow(S0[g], exp(sum_beta_x - SUM_BETA_REFERENCES[g]));
}

/* ΖΗΤΟΥΜΕΝΟ ε) υλοποίηση συνάρτησης
   Μετατρέπει την δεκαδική τιμή του ρίσκου σε κατηγορία κινδύνου και την εκτυπώνει */
void risk_category(double risk){
    double p = risk * 100;
    printf("Κατηγορία: ");
    if (p < 5){
       printf("Χαμηλός κίνδυνος\n"); 
    } else if (p < 10) {
        printf("Μέτριος κίνδυνος\n");
    } 
    else if (p < 20){
      printf("Υψηλός κίνδυνος\n");  
    } else {printf("Πολύ υψηλός κίνδυνος\n");
    }
}
