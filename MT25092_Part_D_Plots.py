import os
import pandas as pd
import matplotlib.pyplot as plt

# create folder for plots
PLOT_DIR = "plots"
os.makedirs(PLOT_DIR, exist_ok=True)

df = pd.read_csv("MT25092_Part_D_CSV.csv")

def plot_metric(program, worker, metric, ylabel):
    sub = df[(df.Program == program) & (df.Worker == worker)]

    plt.figure()
    plt.plot(sub["Count"], sub[metric], marker='o')
    plt.xlabel("Count (Processes/Threads)")
    plt.ylabel(ylabel)
    plt.title(f"{program} - {worker} - {ylabel}")
    plt.grid(True)

    fname = f"MT25092_{program}_{worker}_{metric}.png"
    save_path = os.path.join(PLOT_DIR, fname)   # ✅ save inside folder

    plt.savefig(save_path)
    print("Saved", save_path)
    plt.close()

for program in ["A", "B"]:
    for worker in ["cpu", "mem", "io"]:
        plot_metric(program, worker, "Time_Seconds", "Execution Time (s)")
        plot_metric(program, worker, "CPU_Percent", "CPU Utilization (%)")
