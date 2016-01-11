import pandas as pd
import numpy as np

txt_begin = \
    "#include \"gift_testing_data.h\" \n"



txt_end =      \
    "const std::vector<Gift> & static_data::gifts_values(){ \n" \
    "    return ___gifts_values; \n" \
    "}; \n" \
    "" \
    "const std::vector<Route> &static_data::solution6(){ \n" \
    "    return ___solution6_values; \n" \
    "}; \n" \
    ""

def generate(gifts_dataframe, all_trips):
    s2 = generate_trips(all_trips)
    s1 = generate_gifts(gifts_dataframe)

    res_str = txt_begin + s1 + "\n" + "\n" + s2 +"\n"+ txt_end

    fn="/home/alexey/development/cpp_projects/keggle_santa/testing/gift_testing_data.cpp"
    text_file = open(fn, "w")
    text_file.write(res_str)
    text_file.close()

def generate_trip_weights(trips_dataframe):
    trip_ids  = set()
    for t_id in  trips_dataframe['TripId'].values:
        trip_ids.add(t_id)

    values = []
    for t_id in trip_ids:
        trip = trips_dataframe[trips_dataframe['TripId']==t_id]
        w = weighted_trip_length_v2(trip)
        values.append(w)

    return values;

def generate_trips(trips_dataframe):
    # res_str = [



    trip_ids  = set()
    for t_id in  trips_dataframe['TripId'].values:
        trip_ids.add(t_id)

    values = []
    for t_id in trip_ids:
        trip = trips_dataframe[trips_dataframe['TripId']==t_id]
        z = trip['GiftId'].values
        str_value = "{"+",".join(str(x-1) for x in z)+"}"
        values.append( "__cr_route("+str_value+")" )

    s = ',\n'.join(values)
    s2 =  "{"+s+"}"


    res_str = "std::vector<Route> ___solution6_values = \n" + s2 + ";";
    return res_str


def generate_gifts(gifts_dataframe):
    # res_str = [
    values = []
    for index, row in gifts_dataframe.iterrows():
        id_float = row.values[0]
        id_int = int(round(id_float))

        str_values = [str(id_int)]+ [str(x) for x in row.values[1:]]

        s = ', '.join(str_values)
        s2 =  "{"+s+"}"
        values.append(s2)

    vals = "{\n\t" + "\t,\n".join(values) + "\n};"
    res_str = "\" \n \n"
    res_str += "std::vector<Gift> ___gifts_values = " + vals;
    return res_str


AVG_EARTH_RADIUS = 6371  # in km
north_pole = (90,0)
weight_limit = 1000
sleigh_weight = 10

def haversine_v2(lat1, lng1, lat2, lng2):

    # convert all latitudes/longitudes from decimal degrees to radians
    lat1, lng1, lat2, lng2 = map(np.radians, (lat1, lng1, lat2, lng2))

    # calculate haversine
    lat = lat2 - lat1
    lng = lng2 - lng1
    d = np.sin(lat / 2) ** 2 + np.cos(lat1) * np.cos(lat2) * np.sin(lng / 2) ** 2
    h = 2 * AVG_EARTH_RADIUS * np.arcsin(np.sqrt(d))
    return h

def weighted_trip_length_v2(trip_df):

    lat = np.append(trip_df.Latitude, north_pole[0])
    lng = np.append(trip_df.Longitude, north_pole[1])
    lat1 = np.roll(lat, 1)
    lng1 = np.roll(lng, 1)

    trip_wgts = np.append((trip_df.Weight.sum() - trip_df.Weight.cumsum().shift(1).fillna(0)), 0.0) + sleigh_weight

    trip_dist = haversine_v2(lat1, lng1, lat, lng)

    return trip_dist.dot(trip_wgts)
