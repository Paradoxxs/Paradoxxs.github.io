---
jupyter:
  colab:
    authorship_tag: ABX9TyO6i7+kkKwpfbHG2eRnASlX
    include_colab_link: true
    name: pcap network anlysis.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown colab_type="text" id="view-in-github"}
`<a href="https://colab.research.google.com/github/Paradoxxs/Paradoxxs.github.io/blob/main/pcap_network_anlysis.ipynb" target="_parent">`{=html}`<img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>`{=html}`</a>`{=html}
:::

::: {.cell .markdown id="FO1kkYZtCloZ"}
Using NFStream to convert the pcap file to dataframe, and there after
perform analysis.
:::

::: {.cell .code id="GcC3cKgEb28N"}
``` {.python}
pip install nfstream
```
:::

::: {.cell .code id="c9aNCJ0fV0ZW"}
``` {.python}
import nfstream
from nfstream import NFStreamer, NFPlugin
import pandas as pd
import numpy
from sklearn.ensemble import RandomForestClassifier
```
:::

::: {.cell .code id="Ed-JT7ZcV_AC"}
``` {.python}
df = NFStreamer(source="file.pcap").to_pandas()
df.head()
```
:::

::: {.cell .code id="ATkcY3JO3f1f"}
``` {.python}
timestamp = 'bidirectional_first_seen_ms'
src_ip = 'src_ip'
dst_ip = 'dst_ip'
dst_host = 'requested_server_name'
dst_port = 'dst_port'
bytes_sent = 'src2dst_bytes'

filter = [timestamp, src_ip, dst_ip, dst_host, dst_port, bytes_sent]
groupby = [src_ip, dst_ip, dst_port] #Group the connect together that are the same. 
```
:::

::: {.cell .code id="zXSjYy1N3iBk"}
``` {.python}
df = df.loc[:,filter]
df[timestamp] = pd.to_datetime(df[timestamp], unit='ms')  #Converting ms to datetime
df = df.groupby(groupby).agg(list)
df.reset_index(inplace=True)
df.head()
```
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="PkvAJPrBBKuu" outputId="35578b9f-bdbd-4acc-b17b-7fdc30b3327f"}
``` {.python}
df.shape
```

::: {.output .execute_result execution_count="43"}
    (38, 6)
:::
:::

::: {.cell .code id="Eq4z7lMV3ppD"}
``` {.python}
#ConnectionCount is  by taking each row in the timestamp column, and get the about of connection that have been made
df['ConnectionCount'] = df[timestamp].apply(lambda x: len(x))

#Remove all connection with less then 10 connections, it was choosen because of the small data sample I used, The goal is to reduce the amount of data that need to be processed
df = df.loc[df['ConnectionCount'] > 10]

#Sort the data
df[timestamp] = df[timestamp].apply(lambda x: sorted(x))


df['delta_time'] = df[timestamp].apply(lambda x: pd.Series(x).diff().dt.seconds.dropna().tolist())
df.head()
```
:::

::: {.cell .code id="KFowLjsX3vRI"}
``` {.python}
df['tsLow'] = df['delta_time'].apply(lambda x: np.percentile(np.array(x),25))
df['tsMid'] = df['delta_time'].apply(lambda x: np.percentile(np.array(x), 50))
df['tsHigh'] = df['delta_time'].apply(lambda x: np.percentile(np.array(x), 75))

df['tsBowleyNum'] = df['tsLow'] + df['tsHigh'] - 2 * df['tsMid']
df['tsBowleyDen'] = df['tsHigh'] - df['tsLow']

# tsSkew should equal zero if the denominator equals zero
# bowley skew is unreliable if Q2 = Q1 or Q2 = Q3
df['tsSkew'] = df[['tsLow', 'tsMid', 'tsHigh', 'tsBowleyNum','tsBowleyDen']].apply(
    lambda x: x['tsBowleyNum'] / x['tsBowleyDen'] if x['tsBowleyDen'] !=0 and x['tsMid'] != x['tsLow'] and x['tsMid'] != x['tsHigh'] !=0 else 0.0, axis=1
    )
df['tsMadm'] = df['delta_time'].apply(lambda x: np.median(np.absolute(np.array(x) - np.median(np.array(x)))))
df['tsConnDiv'] = df[f_timestamp].apply(lambda x: (x[-1].to_pydatetime() - x[0].to_pydatetime()).seconds / 90)

# Time delta score calculation
df['tsConnCountScore'] = df.apply(lambda x: 0.0 if x['tsConnDiv'] == 0  else x['ConnectionCount'] / x['tsConnDiv'] if x['ConnectionCount'] / x['tsConnDiv'] < 1.0 else 1.0 , axis=1)
df['tsSkewScore'] = 1.0 - abs(df['tsSkew'])
df['tsMadmScore'] = df['tsMadm'].apply(lambda x: 0 if 1.0 - (x / 30.0) < 0 else 1.0 - (x / 30.0))
df['tsScore'] = (((df['tsSkewScore'] + df['tsMadmScore'] + df['tsConnCountScore']) / 3.0) * 1000) / 1000
```
:::

::: {.cell .code id="HJH8AJGk3wsN"}
``` {.python}
df['dsLow'] = df[f_sent_bytes].apply(lambda x: np.percentile(np.array(x), 25))
df['dsMid'] = df[f_sent_bytes].apply(lambda x: np.percentile(np.array(x), 50))
df['dsHigh'] = df[f_sent_bytes].apply(lambda x: np.percentile(np.array(x), 75))
df['dsBowleyNum'] = df['dsLow'] + df['dsHigh'] - 2 * df['dsMid']
df['dsBowleyDen'] = df['dsHigh'] - df['dsLow']


# dsSkew should equal zero if the denominator equals zero
# bowley skew is unreliable if Q2 = Q1 or Q2 = Q3
df['dsSkew'] = df[['dsLow','dsMid','dsHigh','dsBowleyNum','dsBowleyDen']].apply(
    lambda x: x['dsBowleyNum'] / x['dsBowleyDen'] if x['dsBowleyDen'] != 0 and x['dsMid'] != x['dsLow'] and x['dsMid'] != x['dsHigh'] else 0.0, axis=1
    )
df['dsMadm'] = df[f_sent_bytes].apply(lambda x: np.median(np.absolute(np.array(x) - np.median(np.array(x)))))


# Data size score calculation of sent bytes
df['dsSkewScore'] = 1.0 - abs(df['dsSkew'])
df['dsMadmScore'] = df['dsMadm'].apply(lambda x: 0 if x/ 128.0 < 0 else x/ 128.0)
df['dsSmallnessScore'] = df['dsMid'].apply(lambda x: 0 if 1.0 - x / 8192.0 < 0 else 1.0 - x / 8192.0)
df['dsScore'] = (((df['dsSkewScore'] + df['dsMadmScore'] + df['dsSmallnessScore']) / 3.0) * 1000) / 1000
```
:::

::: {.cell .code id="3i-btTlR3x5g"}
``` {.python}
# Overal Score calculation
df['Score'] = (df['dsScore'] + df['tsScore']) / 2

df.sort_values(by= 'Score', ascending=False, inplace=True)
df.head()
```
:::
