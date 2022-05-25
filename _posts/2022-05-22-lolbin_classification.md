---
jupyter:
  colab:
    name: lolbin classification.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown id="-feK-f-IH_2i"}
LOL bin classification using libLol and LOLBAS project
:::

::: {.cell .code execution_count="2" colab="{\"height\":401,\"base_uri\":\"https://localhost:8080/\"}" id="o_YDeoj-Hoh7" outputId="5ba0ca8c-7ae3-46f2-bb71-0bef0bf85a86"}
``` {.python}
pip install lolc
```

::: {.output .stream .stdout}
:::

::: {.output .display_data}
``` {.json}
{"pip_warning":{"packages":["IPython","numpy","pandas","prompt_toolkit"]}}
```
:::
:::

::: {.cell .code execution_count="22" id="P0urw5TMHt9i"}
``` {.python}
from lol.api import LOLC, PlatformType
import pandas as pd
import csv
```
:::

::: {.cell .code execution_count="10" id="LyAJM7mlNsaq"}
``` {.python}
path = 'path to file'
```
:::

::: {.cell .code execution_count="36" id="kccvPab8WLIV"}
``` {.python}
with open(path) as csvfile:
  csvdata = csv.reader(csvfile)
  data = list(csvdata)
```
:::

::: {.cell .code execution_count="13" id="oOac6Ao7NZu2"}
``` {.python}
data = pd.read_csv(path)
data.columns = ['command']
```
:::

::: {.cell .code id="ayrpwEjrVjF7"}
``` {.python}
data.tail()
```
:::

::: {.cell .code id="vtSKdeLjV6By"}
``` {.python}
lolc=LOLC(PlatformType.WINDOWS) # allowed parameters are PlatformType.LINUX and PlatformType.WINDOWS
classification, tags = lolc(data)
```
:::

::: {.cell .code execution_count="56" id="dA5qE6xEnn2a"}
``` {.python}
with open("Output.txt", "w") as outfile:
  for command, status, tag in zip (data, classification, tags):
    outfile.write(command[0] + "\n")
    outfile.write(status + "\n")
    outfile.write(tag)
    outfile.write("\n\n")
```
:::
