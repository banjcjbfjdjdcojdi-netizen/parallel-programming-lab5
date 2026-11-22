import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results/bench_seq_vs_threads.csv')

base_times = df[df['threads'] == 1].set_index('view')['time']

for view in [1, 2]:
    subset = df[df['view'] == view].sort_values('threads')
    t1 = base_times[view]
    speedup = t1 / subset['time']
    
    plt.figure(figsize=(10, 6))
    plt.plot(subset['threads'], speedup, marker='o', label=f'View {view}')
    plt.plot(subset['threads'], subset['threads'], 'k--', label='Идеальное ускорение', alpha=0.5)
    
    plt.title(f'Ускорение генерации фрактала (View {view})')
    plt.xlabel('Количество потоков')
    plt.ylabel('Ускорение (S = T1 / Tn)')
    plt.xticks(subset['threads'])
    plt.grid(True, ls="--", alpha=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'results/speedup_view{view}.png', dpi=150)
    plt.close()

print("Графики ускорения сохранены в results/")