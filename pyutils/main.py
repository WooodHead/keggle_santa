import pandas as pd
import numpy as np

from cpp_input_data_generator import generate, weighted_trip_length_v2, north_pole, haversine_v2, generate_trip_weights, \
    weight_limit, sleigh_weight


def weighted_reindeer_weariness_v2(all_trips):

    if any(all_trips.groupby('TripId').Weight.sum() > weight_limit - sleigh_weight):
        raise Exception("One of the sleighs over weight limit!")



    return all_trips.groupby('TripId').apply(weighted_trip_length_v2).sum()



def pr(x):
    print(x)

if __name__ == '__main__':

    gifts = pd.read_csv('/home/alexey/santa_data/gifts.csv')
    sample_sub = pd.read_csv('/home/alexey/santa_data/sol7.csv')

    all_trips = sample_sub.merge(gifts, on='GiftId')




    gr = all_trips #.groupby('TripId')
    trip = gr[gr['TripId'] == 0]

    # z = trip['GiftId'].values #apply( pr );
    # zzz = "{"+",".join(str(x-1) for x in z)+"};"
    # print(zzz)
    #
    # www2 = "{"+",".join(str(x) for x in trip['Weight'].values)+"};"
    # print www2
    # w=weighted_trip_length_v2(trip)
    #
    #
    # lat = np.append(trip.Latitude, north_pole[0])
    # lng = np.append(trip.Longitude, north_pole[1])
    # lat1 = np.roll(lat, 1)
    # lng1 = np.roll(lng, 1)
    #
    # trip_dist = haversine_v2(lat1, lng1, lat, lng)
    # dist_str = "{"+",".join(str(x) for x in trip_dist)+"};"
    # print dist_str
    #
    #
    # weights123= generate_trip_weights(all_trips)
    # dist_str = "{"+",".join(str(x) for x in weights123)+"};"
    # print dist_str

    # generate(gifts, all_trips)



    w= (weighted_reindeer_weariness_v2(all_trips))

    print(w)
    #