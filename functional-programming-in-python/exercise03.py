from functools import reduce
from operator import add

countries = [
    {"code": "tur", "name": "turkey", "continent": "asia", "population": 80000000},
    {"code": "fra", "name": "france", "continent": "europe", "population": 67000000},
    {"code": "ita", "name": "italy", "continent": "europe", "population": 90000000}
]

ifEuropean = lambda country: country["continent"] == "europe"
toPopulation = lambda country: country["population"]

total_population = reduce(add, map(toPopulation, filter(ifEuropean, countries)))
print(f"Total population of european countries is {total_population}")

numOfEuropeanCountries = reduce(add, map(lambda country: 1, filter(ifEuropean, countries)))
print(f"Number of european countries is {numOfEuropeanCountries}")
