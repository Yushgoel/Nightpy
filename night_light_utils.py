import numpy as np
import h5py
import PIL
from PIL import Image
import matplotlib.pyplot as plt
import os
import datetime as dt


#Return radiance file from path of h5 file
def return_rad(path):
    hf = h5py.File(path, 'r')
    HDFEOS = hf['HDFEOS']
    grids = HDFEOS['GRIDS']
    vnp = grids['VNP_Grid_DNB']
    data = vnp['Data Fields']
    radiance = data['DNB_At_Sensor_Radiance_500m']
    rad = np.matrix(radiance)
    rad = rad.astype('int16')
    return rad


#Return cloud file from path of h5 file
def return_cloud(path):
    hf = h5py.File(path, 'r')
    HDFEOS = hf['HDFEOS']
    grids = HDFEOS['GRIDS']
    vnp = grids['VNP_Grid_DNB']
    data = vnp['Data Fields']
    cloud_cov = data['QF_Cloud_Mask']
    cloud = np.matrix(cloud_cov)
    cloud = cloud.astype('int16')
    return cloud


#Display the matrix as an image - useful for visualizing night light or cloud coverage
def img_rad(matrix):
    img = Image.fromarray(matrix)
    img.show()


#Extract a sub portion of tile given start and end pixels. Useful for extracting data for specific city.
def city_from_cords(x_start, x_end, y_start, y_end, tile):
    city_matrix = np.zeros(( (y_end - y_start),   (x_end - x_start)  ))
    city_matrix = np.matrix(city_matrix)

    for x in range(x_start, x_end):
        for y in range(y_start, y_end):
            city_matrix[y - y_start, x - x_start] = tile[y, x]

    return city_matrix


#Extract the cloud filter (cloud present or not) from the cloud data file. Use scale_for_img=True when visualizing cloud coverage as image.
def return_cloud_filter(cloud_data, mask_num = 0b11000000, threshold = 125, scale_for_img = False):
    cloud_filter = np.zeros(cloud_data.shape)
    cloud_filter = np.matrix(cloud_filter)

    cloud_filter = cloud_data & mask_num
    cloud_filter = cloud_filter < threshold

    if scale_for_img:
        cloud_filter = cloud_filter * 255

    cloud_filter = cloud_filter.astype('int16')
    return cloud_filter

#Compress tile values into single number. Good for comparisions of same place over time.
def single_loc_mean(tile):
    return tile.mean()


#Given tile number, year, month, start date, and end date, return average Night Light Average for every pixel - Helpful for removing noise.
def week_loc_mean(tile, year, day_start, day_end, month):

    week_tile = np.zeros((2400, 2400))
    week_tile = np.matrix(week_tile)

    for i in range(day_start, day_end + 1):
        day_file = (dt.date(year, month, i) - dt.date(year,1,1)).days + 1
        day_file = str(day_file).zfill(3)
        path = 'A' + str(year) + day_file + '.' + tile + '.h5'
        rad = return_rad('Data/' + path)
        week_tile = week_tile + rad

    week_tile = week_tile / (day_end - day_start + 1)
    return week_tile

#Join multiple tiles to get one bigger image, given list of tiles and shape (num tiles per row) - Helpful for combining adjacent tiles to form country tile.
def join_tiles(tiles, shapes):
    assert len(tiles) == sum(shapes)
    null_tile = np.zeros((2400, 2400))
    null_tile = np.matrix(null_tile)

    big_tile = np.zeros((2400*len(shapes), 2400*max(shapes)))

    index = 0

    for j in range(len(shapes)):
        for i in range(shapes[j]):
            tile = tiles[index]
            big_tile[j*2400 : tile.shape[0] + j*2400, i*2400 : tile.shape[1] + i *2400] = tile
            index += 1

    return big_tile

#Rename Data Files into Desired Format once downloaded. Note that the files to be renamed should be in the Renaming_data folder
def rename_data():
    data = os.listdir('./Renaming_data')
    print("Starting Renaming      ", end="", flush=True)
    for file in data:
        os.rename('./Renaming_data/' + file, './Renaming_data/' + file[8 : 23] + '.h5')
        print(".", end="", flush=True)
    print("Renaming Data Finished")


#Plot the colorwise difference between two tiles: Red is decrease, Green is increase
def plot_diff_filter(m2, m1, p_decline=0, p_increase=0):
    diff = m2 - m1
    inc = np.multiply(diff, (diff>0))
    inc = np.multiply(inc, ((inc / m1) > p_increase))
    dcr = np.abs(np.multiply(diff, (diff<0)))
    dcr = np.multiply(dcr, ((dcr / m1) > p_decline))

    gr = np.zeros(inc.shape)
    rgb = np.array([dcr, inc ,gr])
    temp = np.dstack(rgb)
    temp = temp / np.amax(diff)
    rgbArray = np.zeros((gr.shape[0],gr.shape[1],3), 'uint8')
    rgbArray[..., 0] = temp[:, :, 0] * 255
    rgbArray[..., 1] = temp[:, :, 1] * 255
    rgbArray[..., 2] = temp[:, :, 2] * 255
    img = Image.fromarray(rgbArray)
    img.show()



#Plot the Histogram of pixel intensity values. Can use Multiple tiles. Useful for seeing whether high intensity pixel value places went up or down. (places that are bright - did they become dim or not)
def light_hist(tiles, legend, bins=100):
    for i in tiles:
        plt.hist(i.reshape(i.shape[0]*i.shape[1], 1), bins=bins)
    plt.legend(legend)
    plt.show()
