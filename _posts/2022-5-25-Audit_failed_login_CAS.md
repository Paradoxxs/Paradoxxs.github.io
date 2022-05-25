---
jupyter:
  colab:
    authorship_tag: ABX9TyOaBjUJc41Pp3oa7POLC0OT
    include_colab_link: true
    name: Audit failed login CAS.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown colab_type="text" id="view-in-github"}
`<a href="https://colab.research.google.com/github/Paradoxxs/Paradoxxs.github.io/blob/main/Audit_failed_login_CAS.ipynb" target="_parent">`{=html}`<img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>`{=html}`</a>`{=html}
:::

::: {.cell .markdown id="LIq4kO7itkgo"}
Using data science til at lave audit af failed logins, Data er fra Cloud
app secturity
:::

::: {.cell .code execution_count="36" id="T3HNUjKgKMiy"}
``` {.python}
import pandas as pd
```
:::

::: {.cell .code execution_count="56" id="NcUfKuzpKOUc"}
``` {.python}
df = pd.read_csv("activity_log.csv")
filter = ['User', 'Device', 'IP address', 'Date']
```
:::

::: {.cell .code execution_count="57" colab="{\"height\":206,\"base_uri\":\"https://localhost:8080/\"}" id="fwsjYPfGKfaO" outputId="719717e5-3ae8-4350-8724-f41ae59afe29"}
``` {.python}
df = df.loc[:,filter]
df["Date"] = pd.to_datetime(df["Date"])  #Converting ms to datetime
df = df.groupby(["User","Device"]).agg(list)
df.reset_index(inplace=True)
df.head()
```

::: {.output .execute_result execution_count="57"}
```{=html}
  <div id="df-24e2ae9f-8769-4952-aa71-621b1e80edb6">
    <div class="colab-df-container">
      <div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>User</th>
      <th>Device</th>
      <th>IP address</th>
      <th>Date</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Aase Bjerregaard Christensen</td>
      <td>AADCONNECT-A1</td>
      <td>[10.0.0.49, 10.0.0.49]</td>
      <td>[2022-02-04 07:45:57.186000+00:00, 2022-02-04 ...</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Abel Møller</td>
      <td>ISE-P1</td>
      <td>[nan]</td>
      <td>[2022-02-04 08:06:09.364000+00:00]</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Adam Victor Hansen Nørgaard</td>
      <td>FRONTJUMP-P1</td>
      <td>[10.2.25.11]</td>
      <td>[2022-02-04 09:26:03.313000+00:00]</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Adam Victor Hansen Nørgaard</td>
      <td>FRONTJUMP-P2</td>
      <td>[10.2.25.12]</td>
      <td>[2022-02-04 08:45:35.882000+00:00]</td>
    </tr>
    <tr>
      <th>4</th>
      <td>Adam Victor Hansen Nørgaard</td>
      <td>ISE-P1</td>
      <td>[nan, nan, nan, nan, nan, nan, nan, nan, nan, ...</td>
      <td>[2022-02-04 09:31:45.758000+00:00, 2022-02-04 ...</td>
    </tr>
  </tbody>
</table>
</div>
      <button class="colab-df-convert" onclick="convertToInteractive('df-24e2ae9f-8769-4952-aa71-621b1e80edb6')"
              title="Convert this dataframe to an interactive table."
              style="display:none;">
        
  <svg xmlns="http://www.w3.org/2000/svg" height="24px"viewBox="0 0 24 24"
       width="24px">
    <path d="M0 0h24v24H0V0z" fill="none"/>
    <path d="M18.56 5.44l.94 2.06.94-2.06 2.06-.94-2.06-.94-.94-2.06-.94 2.06-2.06.94zm-11 1L8.5 8.5l.94-2.06 2.06-.94-2.06-.94L8.5 2.5l-.94 2.06-2.06.94zm10 10l.94 2.06.94-2.06 2.06-.94-2.06-.94-.94-2.06-.94 2.06-2.06.94z"/><path d="M17.41 7.96l-1.37-1.37c-.4-.4-.92-.59-1.43-.59-.52 0-1.04.2-1.43.59L10.3 9.45l-7.72 7.72c-.78.78-.78 2.05 0 2.83L4 21.41c.39.39.9.59 1.41.59.51 0 1.02-.2 1.41-.59l7.78-7.78 2.81-2.81c.8-.78.8-2.07 0-2.86zM5.41 20L4 18.59l7.72-7.72 1.47 1.35L5.41 20z"/>
  </svg>
      </button>
      
  <style>
    .colab-df-container {
      display:flex;
      flex-wrap:wrap;
      gap: 12px;
    }

    .colab-df-convert {
      background-color: #E8F0FE;
      border: none;
      border-radius: 50%;
      cursor: pointer;
      display: none;
      fill: #1967D2;
      height: 32px;
      padding: 0 0 0 0;
      width: 32px;
    }

    .colab-df-convert:hover {
      background-color: #E2EBFA;
      box-shadow: 0px 1px 2px rgba(60, 64, 67, 0.3), 0px 1px 3px 1px rgba(60, 64, 67, 0.15);
      fill: #174EA6;
    }

    [theme=dark] .colab-df-convert {
      background-color: #3B4455;
      fill: #D2E3FC;
    }

    [theme=dark] .colab-df-convert:hover {
      background-color: #434B5C;
      box-shadow: 0px 1px 3px 1px rgba(0, 0, 0, 0.15);
      filter: drop-shadow(0px 1px 2px rgba(0, 0, 0, 0.3));
      fill: #FFFFFF;
    }
  </style>

      <script>
        const buttonEl =
          document.querySelector('#df-24e2ae9f-8769-4952-aa71-621b1e80edb6 button.colab-df-convert');
        buttonEl.style.display =
          google.colab.kernel.accessAllowed ? 'block' : 'none';

        async function convertToInteractive(key) {
          const element = document.querySelector('#df-24e2ae9f-8769-4952-aa71-621b1e80edb6');
          const dataTable =
            await google.colab.kernel.invokeFunction('convertToInteractive',
                                                     [key], {});
          if (!dataTable) return;

          const docLinkHtml = 'Like what you see? Visit the ' +
            '<a target="_blank" href=https://colab.research.google.com/notebooks/data_table.ipynb>data table notebook</a>'
            + ' to learn more about interactive tables.';
          element.innerHTML = '';
          dataTable['output_type'] = 'display_data';
          await google.colab.output.renderOutput(dataTable, element);
          const docLink = document.createElement('div');
          docLink.innerHTML = docLinkHtml;
          element.appendChild(docLink);
        }
      </script>
    </div>
  </div>
  
```
:::
:::

::: {.cell .code execution_count="58" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="8SNJ-RBhLGts" outputId="e097aa22-b23f-464a-ccb4-6a78b5cbf463"}
``` {.python}
df['login_counts'] = df["Date"].apply(lambda x: len(x))
df = df.loc[df['login_counts'] > 10]
df["Date"] = df["Date"].apply(lambda x: sorted(x))
df['delta_time'] = df["Date"].apply(lambda x: pd.Series(x).diff().dt.seconds.dropna().tolist())
```

::: {.output .stream .stderr}
    /usr/local/lib/python3.7/dist-packages/ipykernel_launcher.py:3: SettingWithCopyWarning: 
    A value is trying to be set on a copy of a slice from a DataFrame.
    Try using .loc[row_indexer,col_indexer] = value instead

    See the caveats in the documentation: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy
      This is separate from the ipykernel package so we can avoid doing imports until
    /usr/local/lib/python3.7/dist-packages/ipykernel_launcher.py:4: SettingWithCopyWarning: 
    A value is trying to be set on a copy of a slice from a DataFrame.
    Try using .loc[row_indexer,col_indexer] = value instead

    See the caveats in the documentation: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy
      after removing the cwd from sys.path.
:::
:::

::: {.cell .code execution_count="59" colab="{\"height\":990,\"base_uri\":\"https://localhost:8080/\"}" id="A6ZFWPb1Ljyn" outputId="015d6434-cc9a-4346-d56f-4bf4a2dcb720"}
``` {.python}
df.sort_values(by=['login_counts'], ascending=False, inplace=True)
df.head(30)
```

::: {.output .execute_result execution_count="59"}
```{=html}
  <div id="df-1eb12452-ddcb-451f-a106-ed0be959637b">
    <div class="colab-df-container">
      <div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>User</th>
      <th>Device</th>
      <th>IP address</th>
      <th>Date</th>
      <th>login_counts</th>
      <th>delta_time</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>325</th>
      <td>Nils Thorsted T1</td>
      <td>SJ-T1-CTX</td>
      <td>[nan, nan, nan, nan, nan, nan, nan, nan, nan, ...</td>
      <td>[2022-02-04 05:16:58.449000+00:00, 2022-02-04 ...</td>
      <td>153</td>
      <td>[124.0, 63.0, 123.0, 124.0, 125.0, 67.0, 62.0,...</td>
    </tr>
    <tr>
      <th>124</th>
      <td>Heins Christensen T0</td>
      <td>SJ-T0</td>
      <td>[10.0.24.133, 10.0.24.133, nan, 10.0.24.133, n...</td>
      <td>[2022-02-04 05:16:00.768000+00:00, 2022-02-04 ...</td>
      <td>112</td>
      <td>[0.0, 85.0, 0.0, 0.0, 1.0, 218.0, 0.0, 304.0, ...</td>
    </tr>
    <tr>
      <th>110</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>SJ-T1-CTX</td>
      <td>[10.1.16.28, nan, 10.1.16.28, nan, 10.1.16.28,...</td>
      <td>[2022-02-04 05:17:52.396000+00:00, 2022-02-04 ...</td>
      <td>111</td>
      <td>[1.0, 300.0, 1.0, 300.0, 1.0, 301.0, 1.0, 300....</td>
    </tr>
    <tr>
      <th>322</th>
      <td>Nils Thorsted T1</td>
      <td>FS-P2</td>
      <td>[nan, 10.1.8.60, nan, 10.1.8.60, nan, 10.1.8.6...</td>
      <td>[2022-02-04 05:17:28.767000+00:00, 2022-02-04 ...</td>
      <td>108</td>
      <td>[1.0, 318.0, 1.0, 318.0, 1.0, 318.0, 1.0, 318....</td>
    </tr>
    <tr>
      <th>109</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>EMMA-P1</td>
      <td>[10.1.10.35, nan, 10.1.10.35, nan, 10.1.10.35,...</td>
      <td>[2022-02-04 05:19:26.566000+00:00, 2022-02-04 ...</td>
      <td>108</td>
      <td>[0.0, 319.0, 0.0, 319.0, 0.0, 319.0, 0.0, 319....</td>
    </tr>
    <tr>
      <th>114</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>VEEAMO-P1</td>
      <td>[10.1.10.32, nan, 10.1.10.32, nan, 10.1.10.32,...</td>
      <td>[2022-02-04 05:19:19.877000+00:00, 2022-02-04 ...</td>
      <td>106</td>
      <td>[1.0, 301.0, 1.0, 302.0, 1.0, 300.0, 1.0, 301....</td>
    </tr>
    <tr>
      <th>321</th>
      <td>Nils Thorsted T1</td>
      <td>FS-P1</td>
      <td>[10.1.8.41, nan, 10.1.8.41, nan, 10.1.8.41, na...</td>
      <td>[2022-02-04 05:18:53.678000+00:00, 2022-02-04 ...</td>
      <td>105</td>
      <td>[1.0, 197.0, 1.0, 120.0, 1.0, 318.0, 1.0, 318....</td>
    </tr>
    <tr>
      <th>182</th>
      <td>Johannes Uldal T1</td>
      <td>TOTALVIEW-P1</td>
      <td>[10.1.10.51, nan, 10.1.10.51, 10.1.10.51, nan,...</td>
      <td>[2022-02-04 05:20:15.847000+00:00, 2022-02-04 ...</td>
      <td>105</td>
      <td>[0.0, 341.0, 0.0, 341.0, 0.0, 341.0, 0.0, 341....</td>
    </tr>
    <tr>
      <th>285</th>
      <td>Mikael Ivarsson T1</td>
      <td>SJ-T1</td>
      <td>[10.1.24.133, nan, 10.1.24.133, nan, 10.1.24.1...</td>
      <td>[2022-02-04 05:19:53.975000+00:00, 2022-02-04 ...</td>
      <td>104</td>
      <td>[1.0, 306.0, 1.0, 307.0, 1.0, 308.0, 1.0, 308....</td>
    </tr>
    <tr>
      <th>108</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>CTXMDT-P1</td>
      <td>[10.1.16.50, nan, 10.1.16.50, 10.1.16.50, nan,...</td>
      <td>[2022-02-04 05:16:30.633000+00:00, 2022-02-04 ...</td>
      <td>104</td>
      <td>[0.0, 319.0, 0.0, 319.0, 0.0, 319.0, 0.0, 319....</td>
    </tr>
    <tr>
      <th>107</th>
      <td>Frederik Fisker Jespersen T0</td>
      <td>SW-P1</td>
      <td>[10.0.0.15, 10.0.0.15, nan, 10.0.0.15, nan, 10...</td>
      <td>[2022-02-04 05:18:40.650000+00:00, 2022-02-04 ...</td>
      <td>103</td>
      <td>[1.0, 319.0, 1.0, 319.0, 1.0, 319.0, 1.0, 319....</td>
    </tr>
    <tr>
      <th>334</th>
      <td>Ole K Sørensen T1</td>
      <td>TMSCOMDEV-T1</td>
      <td>[10.1.32.17, nan, nan, 10.1.32.17, nan, 10.1.3...</td>
      <td>[2022-02-04 05:17:49.845000+00:00, 2022-02-04 ...</td>
      <td>103</td>
      <td>[0.0, 319.0, 0.0, 319.0, 0.0, 319.0, 0.0, 319....</td>
    </tr>
    <tr>
      <th>324</th>
      <td>Nils Thorsted T1</td>
      <td>SJ-T1</td>
      <td>[10.1.24.133, nan, 10.1.24.133, nan, 10.1.24.1...</td>
      <td>[2022-02-04 05:19:52.072000+00:00, 2022-02-04 ...</td>
      <td>102</td>
      <td>[1.0, 306.0, 1.0, 306.0, 1.0, 307.0, 1.0, 308....</td>
    </tr>
    <tr>
      <th>104</th>
      <td>Frederik Fisker Jespersen T0</td>
      <td>CA-P1</td>
      <td>[10.0.0.13, nan, 10.0.0.13, nan, 10.0.0.13, na...</td>
      <td>[2022-02-04 05:18:54.401000+00:00, 2022-02-04 ...</td>
      <td>99</td>
      <td>[0.0, 319.0, 0.0, 319.0, 0.0, 319.0, 0.0, 319....</td>
    </tr>
    <tr>
      <th>112</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>TMSCOM-P2</td>
      <td>[10.1.8.158, 10.1.8.158, nan, 10.1.8.158, nan,...</td>
      <td>[2022-02-04 05:19:18.736000+00:00, 2022-02-04 ...</td>
      <td>97</td>
      <td>[0.0, 339.0, 0.0, 339.0, 0.0, 339.0, 0.0, 339....</td>
    </tr>
    <tr>
      <th>187</th>
      <td>Jonas Ahmed T1</td>
      <td>TMSCOM-P2</td>
      <td>[nan, 10.1.8.158, nan, 10.1.8.158, nan, 10.1.8...</td>
      <td>[2022-02-04 05:18:59.106000+00:00, 2022-02-04 ...</td>
      <td>97</td>
      <td>[0.0, 339.0, 0.0, 339.0, 0.0, 339.0, 0.0, 339....</td>
    </tr>
    <tr>
      <th>265</th>
      <td>Martin Hildebrandt Jensen T1</td>
      <td>MEDIUS-P1</td>
      <td>[10.1.8.47, nan, nan, 10.1.8.47, nan, 10.1.8.4...</td>
      <td>[2022-02-04 05:20:54.647000+00:00, 2022-02-04 ...</td>
      <td>97</td>
      <td>[1.0, 340.0, 1.0, 340.0, 1.0, 340.0, 1.0, 338....</td>
    </tr>
    <tr>
      <th>283</th>
      <td>Mikael Ivarsson T1</td>
      <td>MEDIUS-P1</td>
      <td>[10.1.8.47, nan, 10.1.8.47, nan, 10.1.8.47, na...</td>
      <td>[2022-02-04 05:21:15.436000+00:00, 2022-02-04 ...</td>
      <td>96</td>
      <td>[1.0, 340.0, 1.0, 340.0, 1.0, 339.0, 1.0, 339....</td>
    </tr>
    <tr>
      <th>133</th>
      <td>Heins Christensen T1</td>
      <td>TMSCOM-T1</td>
      <td>[10.1.32.136, nan, 10.1.32.136, nan, 10.1.32.1...</td>
      <td>[2022-02-04 05:15:59.480000+00:00, 2022-02-04 ...</td>
      <td>94</td>
      <td>[0.0, 358.0, 0.0, 358.0, 0.0, 358.0, 0.0, 135....</td>
    </tr>
    <tr>
      <th>113</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>TMSCOM-T1</td>
      <td>[10.1.32.136, nan, 10.1.32.136, nan, 10.1.32.1...</td>
      <td>[2022-02-04 05:16:19.193000+00:00, 2022-02-04 ...</td>
      <td>90</td>
      <td>[0.0, 358.0, 0.0, 358.0, 0.0, 358.0, 0.0, 358....</td>
    </tr>
    <tr>
      <th>333</th>
      <td>Ole K Sørensen T1</td>
      <td>TMSCOM-P1</td>
      <td>[10.1.8.52, nan, 10.1.8.52, nan, 10.1.8.52, na...</td>
      <td>[2022-02-04 05:19:21.701000+00:00, 2022-02-04 ...</td>
      <td>88</td>
      <td>[1.0, 377.0, 1.0, 377.0, 1.0, 377.0, 1.0, 377....</td>
    </tr>
    <tr>
      <th>185</th>
      <td>Jonas Ahmed T1</td>
      <td>SJ-T1</td>
      <td>[10.1.24.133, nan, 10.1.24.133, nan, 10.1.24.1...</td>
      <td>[2022-02-04 05:19:57.530000+00:00, 2022-02-04 ...</td>
      <td>88</td>
      <td>[1.0, 307.0, 1.0, 307.0, 1.0, 308.0, 1.0, 307....</td>
    </tr>
    <tr>
      <th>111</th>
      <td>Frederik Fisker Jespersen T1</td>
      <td>TMSCOM-P1</td>
      <td>[10.1.8.52, nan, 10.1.8.52, nan, 10.1.8.52, na...</td>
      <td>[2022-02-04 05:19:41.437000+00:00, 2022-02-04 ...</td>
      <td>88</td>
      <td>[1.0, 377.0, 1.0, 377.0, 1.0, 377.0, 1.0, 377....</td>
    </tr>
    <tr>
      <th>186</th>
      <td>Jonas Ahmed T1</td>
      <td>TMSCOM-P1</td>
      <td>[10.1.8.52, nan, 10.1.8.52, 10.1.8.52, nan, 10...</td>
      <td>[2022-02-04 05:20:01.181000+00:00, 2022-02-04 ...</td>
      <td>85</td>
      <td>[1.0, 377.0, 1.0, 299.0, 1.0, 76.0, 1.0, 377.0...</td>
    </tr>
    <tr>
      <th>188</th>
      <td>Jonas Ahmed T1</td>
      <td>TMSCOM-T1</td>
      <td>[10.1.32.136, nan, 10.1.32.136, 10.1.32.136, n...</td>
      <td>[2022-02-04 05:21:38.771000+00:00, 2022-02-04 ...</td>
      <td>85</td>
      <td>[0.0, 358.0, 0.0, 358.0, 0.0, 358.0, 0.0, 358....</td>
    </tr>
    <tr>
      <th>131</th>
      <td>Heins Christensen T1</td>
      <td>TMSCOM-P1</td>
      <td>[nan, 10.1.8.52, nan, nan, 10.1.8.52, nan, 10....</td>
      <td>[2022-02-04 05:20:20.701000+00:00, 2022-02-04 ...</td>
      <td>84</td>
      <td>[1.0, 377.0, 1.0, 377.0, 1.0, 377.0, 1.0, 377....</td>
    </tr>
    <tr>
      <th>396</th>
      <td>Stig Schlosser Lauridsen</td>
      <td>SJ-T2</td>
      <td>[10.2.24.133, nan, 10.2.24.133, nan, 10.2.24.1...</td>
      <td>[2022-02-04 05:35:38.817000+00:00, 2022-02-04 ...</td>
      <td>71</td>
      <td>[1.0, 4558.0, 0.0, 206.0, 0.0, 303.0, 0.0, 302...</td>
    </tr>
    <tr>
      <th>319</th>
      <td>Nils Thorsted T0</td>
      <td>SJ-T0</td>
      <td>[10.0.24.133, nan, 10.0.24.133, nan, 10.0.24.1...</td>
      <td>[2022-02-04 05:16:02.337000+00:00, 2022-02-04 ...</td>
      <td>70</td>
      <td>[0.0, 305.0, 0.0, 304.0, 0.0, 304.0, 0.0, 303....</td>
    </tr>
    <tr>
      <th>105</th>
      <td>Frederik Fisker Jespersen T0</td>
      <td>SJ-T0</td>
      <td>[10.0.24.133, nan, 10.0.24.133, nan, 10.0.24.1...</td>
      <td>[2022-02-04 05:21:04.637000+00:00, 2022-02-04 ...</td>
      <td>68</td>
      <td>[0.0, 304.0, 0.0, 304.0, 0.0, 305.0, 0.0, 302....</td>
    </tr>
    <tr>
      <th>308</th>
      <td>Niclas Benjamin Nielsen</td>
      <td>ISE-P2</td>
      <td>[nan, nan, nan, nan, nan, nan, nan, nan, nan, ...</td>
      <td>[2022-02-04 05:21:28.590000+00:00, 2022-02-04 ...</td>
      <td>59</td>
      <td>[953.0, 334.0, 1616.0, 735.0, 406.0, 133.0, 36...</td>
    </tr>
  </tbody>
</table>
</div>
      <button class="colab-df-convert" onclick="convertToInteractive('df-1eb12452-ddcb-451f-a106-ed0be959637b')"
              title="Convert this dataframe to an interactive table."
              style="display:none;">
        
  <svg xmlns="http://www.w3.org/2000/svg" height="24px"viewBox="0 0 24 24"
       width="24px">
    <path d="M0 0h24v24H0V0z" fill="none"/>
    <path d="M18.56 5.44l.94 2.06.94-2.06 2.06-.94-2.06-.94-.94-2.06-.94 2.06-2.06.94zm-11 1L8.5 8.5l.94-2.06 2.06-.94-2.06-.94L8.5 2.5l-.94 2.06-2.06.94zm10 10l.94 2.06.94-2.06 2.06-.94-2.06-.94-.94-2.06-.94 2.06-2.06.94z"/><path d="M17.41 7.96l-1.37-1.37c-.4-.4-.92-.59-1.43-.59-.52 0-1.04.2-1.43.59L10.3 9.45l-7.72 7.72c-.78.78-.78 2.05 0 2.83L4 21.41c.39.39.9.59 1.41.59.51 0 1.02-.2 1.41-.59l7.78-7.78 2.81-2.81c.8-.78.8-2.07 0-2.86zM5.41 20L4 18.59l7.72-7.72 1.47 1.35L5.41 20z"/>
  </svg>
      </button>
      
  <style>
    .colab-df-container {
      display:flex;
      flex-wrap:wrap;
      gap: 12px;
    }

    .colab-df-convert {
      background-color: #E8F0FE;
      border: none;
      border-radius: 50%;
      cursor: pointer;
      display: none;
      fill: #1967D2;
      height: 32px;
      padding: 0 0 0 0;
      width: 32px;
    }

    .colab-df-convert:hover {
      background-color: #E2EBFA;
      box-shadow: 0px 1px 2px rgba(60, 64, 67, 0.3), 0px 1px 3px 1px rgba(60, 64, 67, 0.15);
      fill: #174EA6;
    }

    [theme=dark] .colab-df-convert {
      background-color: #3B4455;
      fill: #D2E3FC;
    }

    [theme=dark] .colab-df-convert:hover {
      background-color: #434B5C;
      box-shadow: 0px 1px 3px 1px rgba(0, 0, 0, 0.15);
      filter: drop-shadow(0px 1px 2px rgba(0, 0, 0, 0.3));
      fill: #FFFFFF;
    }
  </style>

      <script>
        const buttonEl =
          document.querySelector('#df-1eb12452-ddcb-451f-a106-ed0be959637b button.colab-df-convert');
        buttonEl.style.display =
          google.colab.kernel.accessAllowed ? 'block' : 'none';

        async function convertToInteractive(key) {
          const element = document.querySelector('#df-1eb12452-ddcb-451f-a106-ed0be959637b');
          const dataTable =
            await google.colab.kernel.invokeFunction('convertToInteractive',
                                                     [key], {});
          if (!dataTable) return;

          const docLinkHtml = 'Like what you see? Visit the ' +
            '<a target="_blank" href=https://colab.research.google.com/notebooks/data_table.ipynb>data table notebook</a>'
            + ' to learn more about interactive tables.';
          element.innerHTML = '';
          dataTable['output_type'] = 'display_data';
          await google.colab.output.renderOutput(dataTable, element);
          const docLink = document.createElement('div');
          docLink.innerHTML = docLinkHtml;
          element.appendChild(docLink);
        }
      </script>
    </div>
  </div>
  
```
:::
:::
