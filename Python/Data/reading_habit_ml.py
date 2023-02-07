# -*- coding: utf-8 -*-
"""Reading_Habit_ML

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1emexTKChvj_ye1bVQqkvdMQ-E3mDOkNP
"""

import pandas as pd
import numpy as np
from google.colab import drive
drive.mount('/content/gdrive')

file = ('/content/gdrive/MyDrive/CS410_FinalProject/reading_habit.csv')
df = pd.read_csv(file) 
df

from pathlib import Path
import os
# File Size
df_path =Path('/content/gdrive/MyDrive/CS410_FinalProject')/'reading_habit.csv'
print(f'File size: {os.path.getsize(df_path) / 1024:0.2f} KiB')

from pathlib import Path

# Finding the Format
def head(filepath, n=7):
    with filepath.open() as f:
        for _ in range(n):
            print(f.readline(), end='')
head(df_path)

"""It is Delimited format since there is a comma that seperate the data values."""

# File Encoding
import chardet
encoding = chardet.detect(df_path.read_bytes())['encoding']
print(f'File encoding: {encoding}')

# Granularity
print("Reading Habit shape:", df.shape)

# Quality Check
df.isnull().sum()

# Scope of the education
df['Education'].value_counts().tail(10)

# Scope of the incomes
df['Incomes'].value_counts().tail(10)

# Scope of the Employement
df['Employement'].value_counts().tail(10)

# Quality of Relationships between Age and Education
display(pd.crosstab(df['Age'], df['Education'])[:10])

# Rename long named feature
df.columns = df.columns.str.replace('How many books did you read during last 12months?', 'N_of_Books')

# Drop features that we are not interested in to answer our questions

new_df = df.drop(columns = ['Read any printed books during last 12months?', 'Read any audiobooks during last 12months?', 'Read any e-books during last 12months?',
                            'Last book you read, you…', 'Do you happen to read any daily news or newspapers?', 'Do you happen to read any magazines or journals?' ], axis=1)

new_df.info()

new_df

#new_df = new_df[new_df['Race'] == 'White']
#new_df

from sklearn.preprocessing import OneHotEncoder, OrdinalEncoder
from sklearn.compose import make_column_transformer
from sklearn.pipeline import make_pipeline
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import GradientBoostingRegressor
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import mean_absolute_error, mean_squared_error
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import mean_absolute_error as mae

import seaborn as sns
# Pairplot for Numerical values in our dataset
sns.pairplot(data=df, diag_kind='kde')

"""From the above plot:

Age follows a normal distribution.

N_of_Books is skewed to the right.
"""

# Plotting Categorical Features
# Sex Feature
sns.countplot(y ='Sex', data = df)
plt.title("Sex Feature Count")
plt.show()

# Race Feature
plot = sns.countplot(y ='Race', data = df)
plot = plt.xticks(rotation='vertical')
plt.title("Race Feature Count")
plt.show()

# Marital status? Feature
plot = sns.countplot(y ='Marital status?', data = df)
plot = plt.xticks(rotation='vertical')
plt.title("Marital status Feature Count")
plt.show()

# Education Feature
plot = sns.countplot(y ='Education', data = df)
plot = plt.xticks(rotation='vertical')
plt.title("Education Feature Count")
plt.show()

# Employement Feature
plot = sns.countplot(y ='Employement', data = df)
plot = plt.xticks(rotation='vertical')
plt.title("Employement Feature Count")
plt.show()

# Incomes Feature
plot = sns.countplot(y ='Incomes', data = df)
plot = plt.xticks(rotation='vertical')
plt.title("Incomes Feature Count")
plt.show()

import seaborn
# plotting qualitative vs quantitative features using box plot
# (Education vs Number of Books) relationship visualization
seaborn.set(style="whitegrid")
seaborn.boxplot(y = 'Education', x = 'N_of_Books?', data = new_df).set(title='Education vs Number of Books')

# (Employement vs Number of Books) relationship visualization
seaborn.boxplot(y = 'Employement', x = 'N_of_Books?', data = new_df).set(title='Employement vs Number of Books')

# (Incomes vs Number of Books) relationship visualization
seaborn.boxplot(y = 'Incomes', x = 'N_of_Books?', data = new_df).set(title='Incomes vs Number of Books')

# The heatmap shows the correlation with numerical values. Numerical values in our dataset are two: AGe and Number of Books
import matplotlib.pyplot as plt
correlation = df.corr()
sns.heatmap(correlation, annot = True, fmt = '.2f', cmap = 'Blues').set(title='Correlation between Age and Number of Books')

"""Correlation values range from -1 (negative correlation)  to +1 (positive correlation), if the value is equal to zero, there is no correlation.
 
 
We observe from the heatmap that the age feature has positive/weak correlation with the N_of_Book feature. 

"""

# Define the upper and lower limit for the age outliers
upper_limit = new_df['Age'].quantile(0.99)
lower_limit = new_df['Age'].quantile(0.01)
print('Upper limit', upper_limit)
print('Lower limit',lower_limit)

# Filtering the outliers from age feature
new_df = new_df[(new_df['Age'] <= 85.0) & (new_df['Age'] >= 16.0)]

# Define the upper and lower limit for the Number of books outliers
upper_limit = new_df['N_of_Books?'].quantile(0.99)
lower_limit = new_df['N_of_Books?'].quantile(0.01)
print('Upper limit',upper_limit)
print('Lower limit',lower_limit)

# Filtering the outliers from Number of books feature
new_df = new_df[(new_df['N_of_Books?'] <= 97.0) & (new_df['N_of_Books?'] >= 0.0)]

# Instantiate OneHotEncoder
ohe = OneHotEncoder(sparse = False)


# Apply OneHotEncoder to the gender column 
ohe.fit_transform(new_df[['Sex']])[:5]

# Apply OneHotEncoder to the gender column 
ohe.fit_transform(new_df[['Race']])[:5]

# Apply OneHotEncoder to the gender column 
ohe.fit_transform(new_df[['Marital status?']])[:5]

# Apply OneHotEncoder to the gender column 
ohe.fit_transform(new_df[['Employement']])[:5]

# Unique values in the Education column
list(new_df['Education'].unique())

# Specify the order for the level of education 
education_categories = ['College graduate',
 'High school graduate',
 'High school incomplete',
 'Some college, no 4-year degree',
 'Post-graduate training/professional school after college',
 'Technical, trade or vocational school AFTER high school',
 'None',
 'Don’t know']

# Instantiate ordinal encoder
oe = OrdinalEncoder(categories = [education_categories])

# Apply ordinal encoder to Education column
oe.fit_transform(new_df[['Education']])[:10]

from sklearn.model_selection import train_test_split
from sklearn import preprocessing

# we dropped incomes feature because when we encoded it as a categorical/ordinal feature, we has an error due to typo error. 
X = new_df.drop('Incomes', axis = 1)
Y = new_df["N_of_Books?"]


# Train test split 
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.2, random_state = 42)

print("X_train shape: ", X_train.shape)
print("Y_train shape: ", Y_train.shape)
print("X_test shape: ", X_test.shape)
print("Y_test shape: ", Y_test.shape)

# Make column transformer which consists of OneHotEncoder and OrdincalEncoder
column_transform = make_column_transformer(
    (ohe, ['Sex', 'Race','Marital status?','Employement']), 
    (oe, ['Education']))

from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.metrics import r2_score, mean_absolute_error, mean_squared_error


# Instantiate pipeline with linear regression
lm = LinearRegression()
lm_pipeline = make_pipeline(column_transform, lm)

# Instantiate pipeline with gradient boosting
gbm = GradientBoostingRegressor()
gbm_pipeline = make_pipeline(column_transform, gbm)

# Instantiate pipeline with Decision Tree
dt = DecisionTreeRegressor()
dt_pipeline = make_pipeline(column_transform, dt)

# Fit pipeline to training set and make predictions on test set 
lm_pipeline.fit(X_train, Y_train)
lm_predictions = lm_pipeline.predict(X_test)
print("First 5 LM predictions: ", list(lm_predictions[:5]))

gbm_pipeline.fit(X_train, Y_train)
gbm_predictions = gbm_pipeline.predict(X_test)
print("First 5 GBM predictions: ", list(gbm_predictions[:5]))

dt_pipeline.fit(X_train, Y_train)
dt_predictions = dt_pipeline.predict(X_test)
print("First 5 DT predictions: ", list(dt_predictions[:5]))

# Compare the number of predictions with the size of test set
print("Number of LM predictions: ", len(lm_predictions))
print("Number of GBM predictions: ", len(gbm_predictions))
print("Number of DT predictions: ", len(dt_predictions))
print("Size of test set: ", len(Y_test))

"""**Models Evaluation:**

Since our dataset has many outliers, we will use Mean Absolute Error and R2 to evaluate our models.
"""

# Calculate mean absolute error and r squared  
lm_mae = mean_absolute_error(lm_predictions, Y_test)
lm_r2 = r2_score(Y_test, lm_predictions)
print("Multiple Linear Regression (MAE): {:.2f}".format(round(lm_mae, 2)))
print("Multiple Linear Regression (r2): {:.2f}".format(round(lm_r2, 2)))
print("")


gbm_mae = mean_absolute_error(gbm_predictions, Y_test)
gbm_r2 = r2_score(Y_test, gbm_predictions)
print("Gradient Boosting Regressor (MAE): {:.2f}".format(round(gbm_mae, 2)))
print("Gradient Boosting Regressor (r2): {:.2f}".format(round(gbm_r2, 2)))
print("")


dt_mae = mean_absolute_error(dt_predictions, Y_test)
dt_r2 = r2_score(Y_test, dt_predictions)
print("Decision Tree Regressor (MAE): {:.2f}".format(round(dt_mae, 2)))
print("Decision Tree Regressor (r2): {:.2f}".format(round(dt_r2, 2)))

"""**For MAE:**

This metric measures the difference between predictions and true value of the predictions.




**For r2:**


This metric compares the model predictions to the mean of our target. Values can range from negative infinity (very poor model) to 1 (perfectly predict the values).

Among the three models, Gradient boosting performs slightly better  
(r2 =0.04) than multiple linear regression(r2 =0.03) and Decision tree (r2 = -0.30) models.
"""

# Actual and Predicted Values
df_lm = pd.DataFrame({'Actual': Y_test, 'Predicted': lm_predictions})
df_lm[:7]

# Difference between actual and predicted values
df_lm['Difference'] = df_lm['Actual'] - df_lm['Predicted']
df_lm[:7]

"""The differences between actual and predicted values are high, which means our lm model is high in variance and not a strong model.



"""

# Actual and Predicted Values
df_gbm = pd.DataFrame({'Actual': Y_test, 'Predicted': gbm_predictions})
df_gbm[:7]

# Difference between actual and predicted values
df_gbm['Difference'] = df_gbm['Actual'] - df_gbm['Predicted']
df_gbm[:7]

"""The differences between actual and predicted values are high, which means our gbm model is high in variance and not a strong model."""

# Actual and Predicted Values
df_dt = pd.DataFrame({'Actual': Y_test, 'Predicted': dt_predictions})
df_dt[:7]

# Difference between actual and predicted values
df_dt['Difference'] = df_dt['Actual'] - df_dt['Predicted']
df_dt[:7]

"""The differences between actual and predicted values are high, which means our dt model is high in variance and not a strong model."""

# Plotting our predictions
plt.figure(figsize=(10,5))
plt.scatter(Y_test, lm_predictions, c = 'palevioletred')
plt.xlabel('Actual Values')
plt.ylabel('Predicted Values')
plt.title("Multiple Linear Regression Model")

# Plotting our predictions
plt.figure(figsize=(10,5))
plt.scatter(Y_test, gbm_predictions, c = 'palevioletred')
plt.xlabel('Actual Values')
plt.ylabel('Predicted Values')
plt.title("Gradien Boosting Model")

# Plotting our predictions
plt.figure(figsize=(10,5))
plt.scatter(Y_test, dt_predictions, c = 'palevioletred')
plt.xlabel('Actual Values')
plt.ylabel('Predicted Values')
plt.title("Decision Tree Model")