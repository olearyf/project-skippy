"""

Frances O'Leary, 8/8/2020 - SkippyParser.py

This program is meant to be used with the following command:
'python SkippyParser.py path\FLIGHTXX.csv' in conjunction
with the Project Skippy model rocket flight computer that
generates these .csv files. After executing this command,
this program should open up a series of graphs depicting the data
from the FLIGHTXX.csv file in a browser.

"""

import plotly.graph_objects as go
from plotly.subplots import make_subplots
import pandas as pd
import re
import sys

# get file via user input and read the data
filename = sys.argv[-1]
df = pd.read_csv(filename)

# define layout for subplots
fig = make_subplots(
    rows=8, cols=1,
    shared_xaxes=True,
    vertical_spacing=0.03,
    specs=[[{"type": "scatter"}],
           [{"type": "scatter"}],
           [{"type": "scatter"}],
           [{"type": "scatter"}],
           [{"type": "scatter"}],
           [{"type": "scatter"}],
           [{"type": "scatter"}],
           [{"type": "table"}]],
    subplot_titles=("Pressure (Pa) vs Time (sec)",
        "Altitude (m) vs Time (sec)",
        "Temperature (C) vs Time (sec)",
        "Acceleration (m/s^2) vs Time (sec)",
        "X Acceleration (m/s^2) vs Time (sec)",
        "Y Acceleration (m/s^2) vs Time (sec)",
        "Z Acceleration (m/s^2) vs Time (sec)",
        "Raw Data Table")
)

# Update xaxis labels
fig.update_xaxes(title_text="Time (seconds)", row=1, col=1)
fig.update_xaxes(title_text="Time (seconds)", row=2, col=1)
fig.update_xaxes(title_text="Time (seconds)", row=3, col=1)
fig.update_xaxes(title_text="Time (seconds)", row=4, col=1)
fig.update_xaxes(title_text="Time (seconds)", row=5, col=1)
fig.update_xaxes(title_text="Time (seconds)", row=6, col=1)
fig.update_xaxes(title_text="Time (seconds)", row=7, col=1)

# Update yaxis labels
fig.update_yaxes(title_text="Pressure (Pa)", row=1, col=1)
fig.update_yaxes(title_text="Altitude (m)", row=2, col=1)
fig.update_yaxes(title_text="Temperature (C)", row=3, col=1)
fig.update_yaxes(title_text="Acceleration (m/s^2)", row=4, col=1)
fig.update_yaxes(title_text="Acceleration (m/s^2)", row=5, col=1)
fig.update_yaxes(title_text="Acceleration (m/s^2)", row=6, col=1)
fig.update_yaxes(title_text="Acceleration (m/s^2)", row=7, col=1)

# add pressure graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["pressure(pa)"],
        mode="lines",
        name="pressure",
        line=dict(color="#007EA7")
    ),
    row=1, col=1
)

# add altitude graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["altitude(m)"],
        mode="lines",
        name="altitude",
        line=dict(color="#4AAD52")
    ),
    row=2, col=1
)

# add temperature graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["temperature(C)"],
        mode="lines",
        name="temperature",
        line=dict(color="#F8C630")
    ),
    row=3, col=1
)

# add xacceleration standalone graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["xAcceleration(m/s^2)"],
        mode="lines",
        name="xAcceleration",
        line=dict(color="#724E91")
    ),
    row=5, col=1
)

# add yacceleration standalone graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["yAcceleration(m/s^2)"],
        mode="lines",
        name="yAcceleration",
        line=dict(color="#66B3FF")
    ),
    row=6, col=1
)

# add zacceleration standalone graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["zAcceleration(m/s^2)"],
        mode="lines",
        name="zAcceleration",
        line=dict(color="#EDE7E3")
    ),
    row=7, col=1
)

# add xacceleration to combined acceleration graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["xAcceleration(m/s^2)"],
        mode="lines",
        name="xAcceleration",
        line=dict(color="#724E91")
    ),
    row=4, col=1
)

# add yacceleration to combined acceleration graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["yAcceleration(m/s^2)"],
        mode="lines",
        name="yAcceleration",
        line=dict(color="#66B3FF")
    ),
    row=4, col=1
)

# add zacceleration to combined acceleration graph
fig.add_trace(
    go.Scatter(
        x=df["time(sec)"],
        y=df["zAcceleration(m/s^2)"],
        mode="lines",
        name="zAcceleration",
        line=dict(color="#EDE7E3")
    ),
    row=4, col=1
)

# add table of raw data
fig.add_trace(
    go.Table(
        header=dict(
            values=["time(sec)", "pressure(pa)", "altitude(m)", "temperature(C)",
            "xAcceleration(m/s^2)", "yAcceleration(m/s^2)", "zAcceleration(m/s^2)"],
            font=dict(size=11),
            align="left"
        ),
        cells=dict(
            values=[df[k].tolist() for k in df.columns[0:]],
            align = "left")
    ),
    row=8, col=1
)

# update and set additional styles
fig.update_layout(
    height=4000,
    showlegend=False,
    title_text="<b>Project Skippy Flight Data Readout</b>",
    font_family="Courier New",
    template="plotly_dark"
)

#render in the browser
fig.write_html('skippy_data.html', auto_open=True)
