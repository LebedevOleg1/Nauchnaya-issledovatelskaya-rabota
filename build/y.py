import numpy as np
import matplotlib.pyplot as plt

class HeatSimulator:
    def __init__(self, L=10.0, nx=50, alpha=0.1, total_time=5.0):
        self.nx = nx          # Количество ячеек
        self.alpha = alpha    # Коэффициент температуропроводности
        self.L = L            # Длина стержня
        
        # Инициализация сетки
        self.x = np.linspace(0, L, nx)
        self.dx = self.x[1] - self.x[0]
        
        # Условия устойчивости
        self.dt = 0.4 * (self.dx**2) / (4 * alpha)
        self.nt = int(total_time / self.dt)
        
        # Массивы данных
        self.T = np.zeros(nx)
        self.T_next = np.zeros(nx)
        
        # Начальные условия
        self.initialize_gaussian(100.0, 1.0)
    
    def initialize_gaussian(self, T0, sigma):
        """Гауссово начальное распределение температуры"""
        x_center = self.L / 2
        self.T = T0 * np.exp(-(self.x - x_center)**2 / (2*sigma**2))
    
    def apply_boundary_conditions(self):
        """Фиксированные граничные условия"""
        self.T[0] = 0.0
        self.T[-1] = 0.0
    
    def step(self):
        """Один шаг по времени"""
        for i in range(1, self.nx-1):
            laplacian = (self.T[i+1] - 2*self.T[i] + self.T[i-1]) / self.dx**2
            self.T_next[i] = self.T[i] + self.alpha * self.dt * laplacian
        
        # Обмен массивов
        self.T, self.T_next = self.T_next, self.T
        self.apply_boundary_conditions()
    
    def simulate(self):
        """Полная симуляция с визуализацией"""
        plt.figure(figsize=(10, 6))
        
        # Начальное состояние
        plt.plot(self.x, self.T, label="Initial")
        
        # Основной цикл
        plot_step = self.nt // 10
        for step in range(self.nt):
            self.step()
            
            if step % plot_step == 0:
                plt.plot(self.x, self.T, label=f"t = {self.dt*step:.2f}")
        
        plt.title("Распределение температуры")
        plt.xlabel("Позиция")
        plt.ylabel("Температура")
        plt.legend()
        plt.grid(True)
        plt.show()

# Запуск симуляции
sim = HeatSimulator(L=10.0, nx=100, alpha=0.1, total_time=2.0)
sim.simulate()