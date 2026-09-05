import pandas as pd
import matplotlib.pyplot as plt
import io


csv_data = """n,cubic_s,cubic_ratio,quad_s,quad_ratio,kadane_s,kadane_ratio
1000,0.105479,0,0.000560894,0,1.843e-06,0
2000,0.76847,7.28553,0.00240012,4.2791,3.557e-06,1.93001
4000,6.18226,8.0449,0.00896567,3.7355,6.893e-06,1.93787
8000,47.4027,7.66753,0.0371697,4.14578,1.4061e-05,2.0399
16000,376.8,7.94892,0.146427,3.93942,2.8463e-05,2.02425
"""

df = pd.read_csv(io.StringIO(csv_data))


fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

#
ax1.plot(df['n'], df['cubic_s'], marker='o', linewidth=2, color='#e74c3c', label='Cúbica O(n³)')
ax1.plot(df['n'], df['quad_s'], marker='s', linewidth=2, color='#f39c12', label='Cuadrática O(n²)')
ax1.plot(df['n'], df['kadane_s'], marker='^', linewidth=2, color='#2ecc71', label='Kadane O(n)')

ax1.set_title('Impacto de la Solución Cúbica (Segundos)', fontsize=13, fontweight='bold')
ax1.set_xlabel('Tamaño de Entrada (n)', fontsize=11)
ax1.set_ylabel('Tiempo de Ejecución (Segundos)', fontsize=11)
ax1.grid(True, linestyle='--', alpha=0.5)
ax1.legend(fontsize=10)

ax2.plot(df['n'], df['quad_s'], marker='s', linewidth=2, color='#f39c12', label='Cuadrática O(n²)')
ax2.plot(df['n'], df['kadane_s'], marker='^', linewidth=2, color='#2ecc71', label='Kadane O(n)')

ax2.set_title('Zoom: Cuadrática vs Kadane (Segundos)', fontsize=13, fontweight='bold')
ax2.set_xlabel('Tamaño de Entrada (n)', fontsize=11)
ax2.set_ylabel('Tiempo de Ejecución (Segundos)', fontsize=11)
ax2.grid(True, linestyle='--', alpha=0.5)
ax2.legend(fontsize=10)

plt.tight_layout()
plt.savefig('curvas_lineales.png', dpi=300, bbox_inches='tight')
plt.show()
