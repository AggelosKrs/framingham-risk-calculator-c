# 🏥 Framingham Heart Study Risk Calculator (C Implementation)

A specialized C-based application that implements the **Framingham Heart Study** algorithm to estimate the 10-year risk of cardiovascular disease. This project demonstrates high-precision mathematical modeling, data validation, and structural programming in C.



## 🛠️ Overview

This tool calculates a patient's cardiovascular risk by processing several biometric factors. It is a prime example of translating complex clinical guidelines into a functional programmatic logic.

### Key Technical Features:
* **Logarithmic Modeling:** Utilizes `math.h` for complex natural logarithm and exponential calculations as required by the Framingham equations.
* **Defensive Programming:** Implements input validation loops (Data Guard) to ensure all biometric entries fall within medically valid ranges.
* **Efficient Data Structures:** Uses a `Patient` struct to encapsulate state and ensure clean data flow between functions.
* **Multi-Factor Logic:** Handles gender-specific coefficients and treatment-adjusted systolic blood pressure logic.



## 🧬 The Algorithm Logic

The application processes the following variables:
* **Demographics:** Age, Gender.
* **Lipid Profile:** Total Cholesterol, HDL Cholesterol.
* **Blood Pressure:** Systolic BP, including Hypertension treatment status.
* **Lifestyle Factors:** Smoking status, Diabetes status.

It then categorizes the results into four risk levels:
1. **Low Risk** (<5%)
2. **Moderate Risk** (5-10%)
3. **High Risk** (10-20%)
4. **Very High Risk** (>20%)

## 🚀 How to Run

1. **Compile:**
   ```bash
   gcc main.c -o risk_calculator -lm
