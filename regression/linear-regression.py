import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures


SENSOR_DATA_FILENAME = "datos.csv"

def main():
    sensor_table = pd.read_csv(SENSOR_DATA_FILENAME)
    plt.figure(1)
    sensor_table  = sensor_table.apply(pd.to_numeric, args=('coerce',))
    sensor_table.plot( x="vol", y="current",grid=True, title="current vs input voltage")
    distance = sensor_table.loc[:, "current"] .to_numpy().reshape(-1,1)
    voltage = sensor_table.loc[:, "vol"] .to_numpy().reshape(-1,1)

    # Regresion 
    polyModel = PolynomialFeatures(degree = 2, include_bias=False)
    poly_features_train = polyModel.fit_transform(voltage)
    poly_model = LinearRegression()
    poly_model.fit(poly_features_train, distance)

    distance_predicts = poly_model.predict(poly_features_train)  
    R2 = poly_model.score(poly_features_train, distance)
    print(f"R2 = {R2}")
    coeffs = poly_model.coef_
    print(f"Coeefs = {coeffs}")
    print(f"inter = {poly_model.intercept_}")
    plt.plot(voltage, distance_predicts)
    plt.savefig("figura.png")

if __name__ == '__main__':
   main()
    