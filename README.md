# Nightpy
Code for using VIIRS Night Light Data

# Jupyter notebooks

<b>Concise_research.ipynb</b> - Contains code for regression between Night Light and GDP (scroll to end). Picked 21 cities for regression and present results.

<b>Download Data.ipynb</b>    - Contains code for downloading only the right Night Light data files. Need to create own account in portal for this.

<b>Pipeline.ipynb</b>         - Contains code for running Night Light pipeline. Shows how to use helper functions for crude analysis.

# Python Code

<b>night_light_utils.py</b>   - Contains helper functions for simple manipulation of data. Check function comments for more details.

<b>report_gen.py</b>          - Generate a report for analysis for chosen dates (modify dates in program) for city entered by user.

# Organization

<b>"Data" Folder</b>          - All Night Light Data downloaded is to be stored here for use by functions in code above.

<b>"Renaming_data" Folder</b> - When downloading data using Jupyter notebook, all files will be initially moved here. Once done downloading, run command "rename_data()" in python. This will rename files in appropriate format, and can be accessed based on dates chosen by user.

<b>"Summaries" Folder</b>     - All summaries generated by report_gen.py are stored here.

<b>"VNP46A1" Folder</b>       - This folder is required for programmatic downloading of data and handling the NASA API
