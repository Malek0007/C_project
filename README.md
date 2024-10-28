# Cryptocurrency Price Prediction using Linear Regression in C language

## Overview
This project is a cryptocurrency price prediction application developed in C, implementing a linear regression model to estimate future prices based on historical data. Using features such as high, low, and open prices, trading volume, and market capitalization, the model is trained to predict the market cap, providing insights into price trends. The model uses gradient descent to optimize the weights (theta values) and evaluates performance on both training and test datasets.

## Features

### Data Ingestion and Preprocessing
- **Reads** historical cryptocurrency data from a CSV file.
- **Normalizes** features to a 0-1 range to improve model accuracy and ensure consistency.

### Feature Matrix Construction
- **Constructs** a feature matrix based on normalized high, low, open prices, volume, and market cap.

### Training using Gradient Descent
- **Implements** gradient descent to iteratively minimize the prediction error.
- **Calculates** and outputs the cost at each iteration, helping to assess the model's learning progress.

### Model Evaluation
- **Splits** data into training and testing sets.
- **Outputs** final cost metrics for both training and test datasets, indicating model accuracy.

### Final Prediction Equation
- **Outputs** a linear regression equation based on learned theta values for each feature, providing a formula to make future predictions.

---

This project demonstrates a practical application of linear regression in C for cryptocurrency price prediction. It is well-suited for educational purposes, financial modeling, and as a foundational approach for predictive analytics in finance.
