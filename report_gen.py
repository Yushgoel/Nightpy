import pandas as pd
import plotly.graph_objs as go
from night_light_utils import *
from plotly.offline import init_notebook_mode, iplot, plot
import plotly as py



lat_longs = {
    'blr_lat': (13.1436111, 12.83388),
    'blr_long': (77.46, 77.78388889),
    'mysore_lat' : (12.3744611, 12.2468304),
    'mysore_long' : (76.5603734, 76.7110062),
    'salem_lat' : (11.7433445, 11.5641257),
    'salem_long' : (78.034283, 78.242311399),
    'bom_lat' : (19.315898, 18.907216),
    'bom_long' : (72.778399, 73.221846),
    'pune_lat' : (18.698978, 18.432714),
    'pune_long' : (73.662993, 74.011603),
    'karnataka_lat' : (16.444482, 11.679891),
    'karnataka_long': (74.298543, 77.93700),
    'delhi_lat' : (28.873679, 28.317670),
    'delhi_long' : (76.910456, 77.582555),
    'surat_lat' : (21.266955, 21.131060),
    'surat_long' : (72.747415, 72.920826),
    'bhopal_lat' : (23.317829, 23.160057),
    'bhopal_long' : (77.300587, 77.509989),
    'jaipur_lat' : (27.009452, 26.755429),
    'jaipur_long' : (75.666172, 75.912764),
    'ahm_lat' : (23.261146, 22.939163),
    'ahm_long' : (72.434385, 72.705903),
    'NY_lat' : (40.989266, 40.479856),
    'NY_long' : (-74.351461, -73.346537),
    'california_lower_lat' : (36.967640, 32.557551),
    'california_lower_long' : (-119.922886, -115.999695),
    'california_upper_lat' : (39.823049, 34.451615),
    'california_upper_long' : (-123.887838, -120.092777),
    'san_diego_lat' : (33.099362, 32.582562),
    'san_diego_long' : (-117.341578, -116.869401),
    'LA_lat' : (34.328695, 33.435326),
    'LA_long' : (-118.722811, -116.958560),
    'SanFBA_lat' : (37.874732, 37.196889),
    'SanFBA_long' : (-122.565049, -121.724266),
    'LasVegas_lat' : (36.339823, 35.912815),
    'LasVegas_long' : (-115.381645, -114.903089),
    'Paris_lat' : (49.343414, 48.417113),
    'Paris_long' : (2.138253, 2.545352),
    'Tehran_lat' : (35.924179, 35.048941),
    'Tehran_long' : (50.922294, 51.836051),
    'chicago_lat' : (42.392790, 41.280936),
    'chicago_long' : (-88.551763, -86.940744),
    'shanghai_lat' : (31.518397, 30.615533),
    'shanghai_long' : (120.837911, 121.966061),
    'mexico_city_lat' : (19.885730, 19.175815),
    'mexico_city_long' : (-99.410912, -98.723546),
    'Tokyo_lat' : (36.041088, 35.181342),
    'Tokyo_long' : (139.271901, 139.929616),
    'blr_krishna_rd_lat' : (12.674936, 12.665422),
    'blr_krishna_rd_long' : (77.974699, 77.981034),
    'blr_krishna_forest_rd_lat' : (12.714323, 12.687609),
    'blr_krishna_forest_rd_long' : (77.894460, 77.924690),
    'bom_surat_rd_lat' : (19.608126, 19.503841),
    'bom_surat_rd_long' : (72.905563, 72.924168),
    'blr_hyd_rd_lat' : (16.891514, 16.869547),
    'blr_hyd_rd_long' : (78.162950, 78.170085),
    'wuhan_lat' : (30.819098, 30.227453),
    'wuhan_long' : (113.996109, 114.658473),
    'HK_lat' : (22.500775, 22.231428),
    'HK_long' : (113.911420, 114.276307),
    'Montreal_lat' : (45.685115, 45.448075),
    'Montreal_long' : (-73.755032, -73.493468),
    'Chennai_lat' : (13.324117, 12.818451),
    'Chennai_long' : (80.095112, 80.405370),
    'Vishaka_lat' : (17.755858, 17.591978),
    'Vishaka_long' : (83.163222, 83.357496),
    'HYD_lat' : (17.534505, 17.275169),
    'HYD_long' : (78.273751, 78.614169),
    'SauPaulo_lat' : (-23.402565, -23.754118),
    'SauPaulo_long' : (-46.766356, -46.360879),
    'Seoul_lat' : (37.633061, 37.350121),
    'Seoul_long' : (126.609159, 127.200089),
    'Miami_lat' : (25.875035, 25.672416),
    'Miami_long' : (-80.319136, -80.117516),
    'Dubai_lat' : (25.262080, 24.871344),
    'Dubai_long' : (54.981199, 55.553674),
    'Bangkok_lat' : (13.951137, 13.513020),
    'Bangkok_long' : (100.280079, 100.873502),
    'Taipei_lat' : (25.212822, 24.952546),
    'Taipei_long' : (121.385579, 121.667942),
    'Sydney_lat' : (-33.644266, -34.110462),
    'Sydney_long' : (150.668698, 151.257291)
}


tiles_cords = {
    'h25v07': (20, 70),
    'h25v06' : (30, 70),
    'h10v04' : (50, -80),
    'h06v05' : (40, -120),
    'h05v05' : (40, -130),
    'h18v04' : (50, 0),
    'h23v05' : (40, 50),
    'h09v04' : (50, -90),
    'h30v05' : (40, 120),
    'h08v07' : (20, -100),
    'h31v05' : (40, 130),
    'h29v05' : (40, 110),
    'h29v06' : (30, 110),
    'h26v07' : (20, 80),
    'h13v11' : (-20, -50),
    'h09v06' : (30, -90),
    'h23v06' : (30, 50),
    'h28v07' : (20,100),
    'h30v06' : (30, 120),
    'h33v12' : (-30, 150)
}

# months = ['oct', 'nov', 'dec', 'jan', 'feb', 'mar', 'apr', 'may', 'jun']
months = ['oct', 'nov', 'dec', 'jan', 'feb', 'mar', 'apr', 'may']
# months = ['jan', 'feb', 'mar', 'apr', 'may']#, 'jun']
#months = ['_2013', '_2014', '_2015', '_2016', '_2017', '_2018', '_2019']


def extract_lat_long(lat_ul, long_ul, lat_br, long_br, tile, start_lat, start_long, hemisphere='n'):

    pixel = 10 / 2400

    lat_ul = int(np.floor((lat_ul - start_lat) / pixel))
    lat_br = int(np.ceil((lat_br - start_lat) / pixel))
    if hemisphere.lower() == 'n':
        lat_ul = -lat_ul
        lat_br = -lat_br

    if (lat_br - lat_ul) < 0 or (long_br - long_ul) < 0:
        raise Exception("Error: Choose the Correct Hemisphere")

    long_ul = int(np.floor((long_ul - start_long) / pixel))
    long_br = int(np.ceil((long_br - start_long) / pixel))

    extract = np.zeros((lat_br - lat_ul, long_br - long_ul))

    for x in range(long_ul, long_br):
        for y in range(lat_ul, lat_br):
            extract[y - lat_ul, x - long_ul] = tile[y, x]

    return extract


def clean_noise(tile, threshold=30):
    return np.multiply(tile, tile > threshold)


def return_category(tile, category):
    if category.lower() == 'commercial':
        return np.multiply(tile, tile >= 500)
    elif category.lower() == 'administrative':
        return np.multiply(tile, (tile >= 190) & (tile < 500))
    elif category.lower() == 'residential':
        return np.multiply(tile, (tile >= 30) & (tile < 190))
    else:
        raise Exception("No category Entered")


weeks_to_use = [(2019, 25, 31, 10), (2019, 23, 29, 11), (2019, 23, 29, 12), (2020, 21,
                                                                            27, 1), (2020, 20, 26, 2), (2020, 21, 27, 3), (2020, 20, 26, 4), (2020, 19, 25, 5)]#, (2020, 18, 24, 6)]
#weeks_to_use = [(2013, 7, 13, 2), (2014, 25, 31, 1), (2015, 16, 22, 2), (2016, 5,
#                                                                 11, 2), (2017, 23, 28, 2), (2018, 13, 19, 2), (2019, 1, 7, 2)]
# weeks_to_use = [(2019, 3, 9, 1), (2019, 2, 8, 2), (2019, 3, 9, 3), (2019, 2, 8, 4), (2019, 2, 8, 5), (2019, 1, 7, 6)]

#weeks_to_use = [(2018, 14, 20, 1), (2018, 13, 19, 2), (2018, 14, 20, 3), (2018, 13, 19, 4), (2018, 12, 18, 5)]
# weeks_to_use = [(2020, 21, 27, 1), (2020, 20, 26, 2), (2020, 21, 27, 3), (2020, 20, 26, 4), (2020, 19, 25, 5)]#, (2020, 18, 24, 6)]

tile = 'h25v07'
tile_var_name = 'h25'
city = 'blr'
hemi = 'n'
bench_mon = 'jan'






def generate_report(tile='h25v07', tile_var_name='h25', city='blr', hemi='n', bench_mon='jan', months=months, weeks_to_use=weeks_to_use):
    for i in range(len(months)):
        year, ds, de, mon = weeks_to_use[i]
        command = months[i] + "_" + tile_var_name + " = week_loc_mean('" + tile + "', " + str(
            year) + ',' + str(ds) + ',' + str(de) + ',' + str(mon) + str(')')
        exec(command, globals())

    for mon in months:
        command = city + "_" + mon + " = extract_lat_long(lat_longs['" + city + "_lat'][0], lat_longs['" + \
            city + "_long'][0], lat_longs['" + city + \
            "_lat'][1], lat_longs['" + city + "_long'][1]"
        command = command + ", " + mon + "_" + tile_var_name + \
            ", tiles_cords['" + tile + "'][0], tiles_cords['" + \
            tile + "'][1], '" + hemi + "')"
        exec(command, globals())

        #command = city + '_' + mon + ' = clean_noise(' + city + '_' + mon + ')'
        #exec(command, globals())

    #img_rad(eval(city + "_" + bench_mon))
    # img_rad(eval(city + "_jan"))
    #img_rad(eval(city + "_feb"))
    #img_rad(eval(city + "_mar"))
    # img_rad(eval(city + "_apr"))
    # img_rad(eval(city + "_may"))
    # img_rad(eval(city + "_jun"))
    plt.set_cmap('Spectral')
    plt.imsave('salem_jan.png', -salem_jan / (np.mean(salem_jan) + 300), vmin=-1, vmax=0)
    plt.imsave('salem_may.png', -salem_may/ (np.mean(salem_jan) + 200), vmin=-1, vmax=0)


    command = "com_filter = (" + city + "_" + bench_mon + ">=500).astype('int')"
    exec(command, globals())
    command = "adm_filter = ((" + city + "_" + bench_mon + " >= 190) & (" + city + "_" + bench_mon + " < 500)).astype('int')"
    exec(command, globals())
    command = "res_filter = ((" + city + "_" + bench_mon + " >= 30) & (" + city + "_" + bench_mon + " < 190)).astype('int')"
    exec(command, globals())

    com_num_track = []
    adm_num_track = []
    res_num_track = []

    for fil in [com_num_track, adm_num_track, res_num_track]:

        for month in months:
            tiles = eval(city + '_' + month)

            if fil == com_num_track:
                temp = np.multiply(tiles >= 500, com_filter)

            elif fil == adm_num_track:
                temp = np.multiply((tiles >= 190) & (tiles < 500), adm_filter)
            else:
                temp = np.multiply((tiles >= 30) & (tiles < 190), res_filter)
            fil.append(temp.sum())

    trace1 = go.Scatter(
        x=months,
        y=com_num_track,
        mode="lines+markers",
        name=city + " COMMERCIAL COUNT",
        marker=dict(color='rgba(16, 112, 2, 0.8)'),
        text=city + " COMMERCIAL COUNT")

    trace2 = go.Scatter(
        x=months,
        y=adm_num_track,
        mode="lines+markers",
        name=city + " ADMINISTRATIVE COUNT",
        marker=dict(color='rgba(255, 0, 0, 0.8)'),
        text=city + " ADMINISTRATIVE COUNT")

    trace3 = go.Scatter(
        x=months,
        y=res_num_track,
        mode="lines+markers",
        name=city + " RESIDENTIAL COUNT",
        marker=dict(color='rgba(0, 0, 255, 0.8)'),
        text=city + " RESIDENTIAL COUNT")

    data = [trace1, trace2, trace3]
    layout = dict(title=city + ' Night Light Category Wise',
                  xaxis=dict(title='Month', ticklen=5, zeroline=False)
                  )
    fig_nop = dict(data=data, layout=layout)

    command = city + "_com_tracking = []"
    exec(command, globals())
    command = city + "_adm_tracking = []"
    exec(command, globals())
    command = city + "_res_tracking = []"
    exec(command, globals())

    track_com_command = ""
    track_adm_command = ""
    track_res_command = ""

    for mon in months:
        command = mon + \
            "_com = np.multiply(" + city + "_" + mon + ", com_filter)"
        exec(command, globals())

        track_com_command += city + \
            "_com_tracking.append(single_loc_mean(" + mon + "_com));"

        command = mon + \
            "_adm = np.multiply(" + city + "_" + mon + ", adm_filter)"
        exec(command, globals())

        track_adm_command += city + \
            "_adm_tracking.append(single_loc_mean(" + mon + "_adm));"

        command = mon + \
            "_res = np.multiply(" + city + "_" + mon + ", res_filter)"
        exec(command, globals())

        track_res_command += city + \
            "_res_tracking.append(single_loc_mean(" + mon + "_res));"

    exec(track_com_command, globals())
    exec(track_adm_command, globals())
    exec(track_res_command, globals())

    trace1 = go.Scatter(
        x=months,
        y=eval(city + "_com_tracking"),
        mode="lines+markers",
        name=city + " COMMERCIAL TRACKING",
        marker=dict(color='rgba(0, 0, 0, 0.8)'),
        text=city + ' COMM Tracking')

    trace2 = go.Scatter(
        x=months,
        y=eval(city + "_adm_tracking"),
        mode="lines+markers",
        name=city + " ADMIN TRACKING",
        marker=dict(color='rgba(255, 255, 0, 0.8)'),
        text=city + " ADMIN TRACKING")

    trace3 = go.Scatter(
        x=months,
        y=eval(city + "_res_tracking"),
        mode="lines+markers",
        name=city + " RESIDENTIAL TRACKING",
        marker=dict(color='rgba(255, 20, 147, 0.8)'),
        text=city + " RESIDENTIAL TRACKING")

    data = [trace1, trace2, trace3]
    layout = dict(title=city + ' Night Light Category Wise',
                  xaxis=dict(title='Month', ticklen=5, zeroline=False)
                  )
    fig_mean = dict(data=data, layout=layout)

    summary = pd.DataFrame()
    summary['months'] = months
    summary[city + ' COM TRACKING'] = eval(city + "_com_tracking")
    summary[city + ' ADM TRACKING'] = eval(city + "_adm_tracking")
    summary[city + ' RES TRACKING'] = eval(city + "_res_tracking")
    summary['NOP COM'] = com_num_track
    summary['NOP ADM'] = adm_num_track
    summary['NOP RES'] = res_num_track
    summary['SUM'] = summary['NOP COM'] + \
        summary['NOP ADM'] + summary['NOP RES']
    summary.to_csv("Summaries/" + city + '_summary.csv', index=False)


    # go.Figure(fig_mean).show()
    # go.Figure(fig_nop).show()

city = input("Please Enter City to Analyze             ")
generate_report(tile='h25v07', tile_var_name='h10', city=city, hemi='n', bench_mon='jan', months=months, weeks_to_use=weeks_to_use)
