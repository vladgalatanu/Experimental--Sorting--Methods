import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

try:
    df = pd.read_csv('results.csv')
except FileNotFoundError:
    print("Error: Could not find 'results.csv'. Make sure it is in the same folder as this script!")
    exit()

df['Time_Seconds_Line'] = pd.to_numeric(df['Time_Seconds'].replace('TIMEOUT', np.nan))
df['Time_Seconds_Penalty'] = pd.to_numeric(df['Time_Seconds'].replace('TIMEOUT', 7.0))

sns.set_theme(style="whitegrid")

print("Generating Figure 1: Linear Scale...")
plt.figure(figsize=(10, 6))
sns.lineplot(data=df[df['DataType'] == 'Random'], x='Size', y='Time_Seconds_Line', hue='Algorithm', marker='o', palette='tab10')
plt.title('All Algorithms on Random Data (Linear Scale)', fontsize=14)
plt.ylabel('Time (Seconds)', fontsize=12)
plt.xlabel('Array Size', fontsize=12)
plt.legend(title='Algorithm', bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.savefig('fig1_all_algos.png')
plt.close()

print("Generating Figure 2: Fast Algorithms...")
fast_algos = ['Merge', 'Quick', 'Heap', 'Counting', 'Radix']
plt.figure(figsize=(10, 6))
sns.lineplot(data=df[(df['DataType'] == 'Random') & (df['Algorithm'].isin(fast_algos))], 
             x='Size', y='Time_Seconds_Line', hue='Algorithm', marker='o', palette='Set2')
plt.title('Fast Algorithms on Random Data', fontsize=14)
plt.ylabel('Time (Seconds)', fontsize=12)
plt.xlabel('Array Size', fontsize=12)
plt.legend(title='Algorithm', bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.savefig('fig2_fast_algos.png')
plt.close()

print("Generating Figure 3: Impact of Data Order...")
plt.figure(figsize=(12, 6))
df_100k = df[(df['Size'] == 100000) & (df['DataType'].isin(['Random', 'Sorted', 'Nearly_Sorted', 'Reverse']))].copy()
sns.barplot(data=df_100k, x='Algorithm', y='Time_Seconds_Penalty', hue='DataType', palette='viridis')
plt.title('Impact of Initial Data Order (Size = 100,000)', fontsize=14)
plt.ylabel('Time (Seconds) [Log Scale]', fontsize=12)
plt.xlabel('Algorithm', fontsize=12)
plt.yscale('log')
plt.legend(title='Data Type')
plt.tight_layout()
plt.savefig('fig3_data_order.png')
plt.close()

print("Generating Figure 4: Insertion Sort Adaptability...")
plt.figure(figsize=(10, 6))
sns.lineplot(data=df[df['Algorithm'] == 'Insertion'], x='Size', y='Time_Seconds_Line', hue='DataType', marker='o', palette='Set1')
plt.title('The Adaptability of Insertion Sort', fontsize=14)
plt.ylabel('Time (Seconds)', fontsize=12)
plt.xlabel('Array Size', fontsize=12)
plt.legend(title='Data Type', bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.savefig('fig4_insertion_sort.png')
plt.close()

print("Generating Figure 5: Log-Log Complexity Proof (BONUS)...")
plt.figure(figsize=(10, 6))
sns.lineplot(data=df[df['DataType'] == 'Random'], x='Size', y='Time_Seconds_Line', hue='Algorithm', marker='o', palette='tab10')
plt.title('Log-Log Plot: Mathematical Proof of Time Complexity', fontsize=14)
plt.ylabel('Time (Seconds) [Log Scale]', fontsize=12)
plt.xlabel('Array Size [Log Scale]', fontsize=12)
plt.xscale('log')
plt.yscale('log')
plt.legend(title='Algorithm', bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.savefig('fig5_log_log_proof.png')
plt.close()

print("Generating Figure 6: Performance Matrix Heatmap (BONUS)...")
plt.figure(figsize=(10, 8))
df_heatmap = df[df['Size'] == 50000].pivot(index='Algorithm', columns='DataType', values='Time_Seconds_Penalty')

sns.heatmap(df_heatmap, annot=True, fmt=".4f", cmap="YlOrRd", cbar_kws={'label': 'Time (Seconds)'}, linewidths=.5)
plt.title('Performance Matrix Heatmap (Size = 50,000)', fontsize=14)
plt.xlabel('Initial Data Distribution', fontsize=12)
plt.ylabel('Algorithm', fontsize=12)
plt.tight_layout()
plt.savefig('fig6_heatmap_matrix.png')
plt.close()

print("\nSuccess! 6 high-quality academic charts have been generated in this folder.")