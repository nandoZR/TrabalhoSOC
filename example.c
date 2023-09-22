#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

// Variáveis simulando a velocidade dos motores
int motorSpeed[4] = { 0, 0, 0, 0 };

// Função que simula a manobra de guinada
void Guinada(void* pvParameters) {
	int sentido = *((int*)pvParameters);
	const int incremento = 100;

	if (sentido != 0 && sentido != 1) {
		printf("Erro: Sentido inválido em Guinada\n");
		vTaskDelete(NULL); // Encerrar a tarefa em caso de erro
	}

	while (1) {
		if (sentido == 1) {
			motorSpeed[0] += incremento;
			motorSpeed[2] += incremento;
		}
		else {
			motorSpeed[1] += incremento;
			motorSpeed[3] += incremento;
		}

		printf("Manobra: Guinada, Sentido: %s, Velocidade dos Motores: [%d, %d, %d, %d]\n",
			sentido == 1 ? "Horário" : "Anti-horário",
			motorSpeed[0], motorSpeed[1], motorSpeed[2], motorSpeed[3]);

		vTaskDelay(pdMS_TO_TICKS(10)); // Atraso de 10ms
	}
}

// Função que simula a manobra de arfagem
void Arfagem(void* pvParameters) {
	int direcao = *((int*)pvParameters);
	const int incremento = 25;

	if (direcao != 0 && direcao != 1) {
		printf("Erro: Direção inválida em Arfagem\n");
		vTaskDelete(NULL); // Encerrar a tarefa em caso de erro
	}

	while (1) {
		if (direcao == 1) {
			motorSpeed[2] += incremento;
			motorSpeed[3] += incremento;
		}
		else {
			motorSpeed[0] += incremento;
			motorSpeed[1] += incremento;
		}

		printf("Manobra: Arfagem, Direção: %s, Velocidade dos Motores: [%d, %d, %d, %d]\n",
			direcao == 1 ? "Frente" : "Trás",
			motorSpeed[0], motorSpeed[1], motorSpeed[2], motorSpeed[3]);

		vTaskDelay(pdMS_TO_TICKS(40)); // Atraso de 40ms
	}
}

// Função que simula a manobra de rolagem
void Rolagem(void* pvParameters) {
	int direcao = *((int*)pvParameters);
	const int incremento = 50;

	if (direcao != 0 && direcao != 1) {
		printf("Erro: Direção inválida em Rolagem\n");
		vTaskDelete(NULL); // Encerrar a tarefa em caso de erro
	}

	while (1) {
		if (direcao == 1) {
			motorSpeed[0] += incremento;
			motorSpeed[3] += incremento;
		}
		else {
			motorSpeed[1] += incremento;
			motorSpeed[2] += incremento;
		}

		printf("Manobra: Rolagem, Direção: %s, Velocidade dos Motores: [%d, %d, %d, %d]\n",
			direcao == 1 ? "Direita" : "Esquerda",
			motorSpeed[0], motorSpeed[1], motorSpeed[2], motorSpeed[3]);

		vTaskDelay(pdMS_TO_TICKS(20)); // Atraso de 20ms
	}
}

int main_(void) {
	int sentido_guinada = 1; // 1 para horário, 0 para anti-horário
	int direcao_arfagem = 1; // 1 para frente, 0 para trás
	int direcao_rolagem = 1; // 1 para direita, 0 para esquerda

	// Inicialize o FreeRTOS e crie as tarefas
	xTaskCreate(Guinada, "Guinada", configMINIMAL_STACK_SIZE, &sentido_guinada, tskIDLE_PRIORITY, NULL);
	xTaskCreate(Arfagem, "Arfagem", configMINIMAL_STACK_SIZE, &direcao_arfagem, tskIDLE_PRIORITY, NULL);
	xTaskCreate(Rolagem, "Rolagem", configMINIMAL_STACK_SIZE, &direcao_rolagem, tskIDLE_PRIORITY, NULL);

	// Inicie o escalonador do FreeRTOS
	vTaskStartScheduler();

	return 0;
}
