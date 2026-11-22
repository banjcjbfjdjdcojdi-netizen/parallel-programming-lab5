import subprocess
import time
import os
import csv


EXE_PATH = os.path.join("build", "Release", "mandelbrot_threads.exe")
THREADS = [1, 2, 3, 4, 5, 6, 7, 8]
VIEWS = [1, 2]
RUNS_PER_CONFIG = 3 

results = []

for view in VIEWS:
    for t in THREADS:
        print(f"Запуск View={view}, Threads={t} ...", end=" ", flush=True)
        times = []
        for _ in range(RUNS_PER_CONFIG):
            start = time.time()

            subprocess.run([EXE_PATH, "--view", str(view), "--threads", str(t)], 
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            end = time.time()
            times.append(end - start)

        avg_time = sum(times) / len(times)
        print(f"{avg_time:.3f} сек")
        
        results.append({
            "view": view,
            "threads": t,
            "time": avg_time
        })

os.makedirs("results", exist_ok=True)
csv_path = os.path.join("results", "bench_seq_vs_threads.csv")
with open(csv_path, "w", newline="") as f:
    writer = csv.DictWriter(f, fieldnames=["view", "threads", "time"])
    writer.writeheader()
    for r in results:
        writer.writerow(r)

print(f"\n✅ Результаты сохранены в {csv_path}")