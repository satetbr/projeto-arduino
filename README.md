# Sistema de Controle de Acesso RFID com Arduino

Um projeto de **controle de acesso por cartão RFID** desenvolvido com Arduino. O sistema autentica usuários através de cartões RFID e controla uma fechadura elétrica (relé) com feedback visual através de LEDs.

## 🎯 Funcionalidades

- **Leitura de Cartões RFID**: Identifica cartões através de um leitor MFRC522
- **Autenticação de Múltiplos Cartões**: Suporta múltiplos cartões autorizados
- **Feedback Visual com LEDs**:
  - 🟨 **LED Amarelo**: Aguardando leitura de cartão
  - 🟩 **LED Verde**: Acesso permitido
  - 🟥 **LED Vermelho**: Acesso negado
- **Controle de Fechadura**: Ativa/desativa um relé para controlar uma fechadura elétrica
- **Monitoramento Serial**: Informações de acesso exibidas no monitor serial

## 📋 Requisitos de Hardware

- **Arduino** (Uno, Mega ou compatível)
- **Leitor RFID MFRC522**
- **3 LEDs** (amarelo, verde, vermelho) com resistores apropriados
- **Relé 5V** (para controlar fechadura ou outro equipamento)
- **Cartões/Tags RFID**
- **Cabo USB** para programação
- **Fonte de alimentação** (5V para Arduino e componentes)

### Pinagem

| Componente | Pino Arduino |
|-----------|-------------|
| MFRC522 SS | 10 |
| MFRC522 RST | 9 |
| LED Amarelo | 5 |
| LED Verde | 6 |
| LED Vermelho | 7 |
| Relé | 4 |


### Configuração de Cartões Autorizados

Edite o arquivo `projeto_arduino.ino` e atualize os números de série dos cartões autorizados:

```cpp
String cartaoAutorizado1 = "90cb9512";
String cartaoAutorizado2 = "7e443143";
```


## 🚀 Como Usar

1. **Energize o Arduino**
2. **Abra o Serial Monitor** (Tools → Serial Monitor, 9600 baud)
3. **Aproxime um cartão RFID** do leitor
4. O sistema verificará se o cartão está autorizado:
   - ✅ **Autorizado**: LED verde acende e relé ativa por 1 segundo
   - ❌ **Não Autorizado**: LED vermelho acende por 4 segundos
5. **LED amarelo** volta a acender, aguardando próximo cartão

## 📊 Fluxo de Funcionamento

```
┌─────────────────────┐
│  Arduino Iniciado   │
│  (LED Amarelo ON)   │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Aguarda Cartão     │
│  (Leitura RFID)     │
└──────────┬──────────┘
           │
    ┌──────┴──────┐
    │             │
    ▼             ▼
┌────────┐   ┌─────────┐
│Valida? │   │ Não     │
│   SIM  │   │ Valida? │
└───┬────┘   └────┬────┘
    │             │
    ▼             ▼
┌─────────┐   ┌──────────┐
│LED Verde│   │LED Vermelho
│Relé ON  │   │1000ms
└─────────┘   └──────────┘
    │             │
    └──────┬──────┘
           ▼
    ┌─────────────┐
    │LED Amarelo  │
    │Volta a ON   │
    └─────────────┘
```

## 🔐 Segurança

⚠️ **Aviso**: Este projeto é educacional e não deve ser usado em ambientes que requerem segurança de produção sem melhorias adicionais:
- Considere adicionar autenticação de dois fatores
- Implemente registro de acesso em banco de dados
- Use cartões/tags com criptografia para aplicações críticas
- Adicione proteção física contra manipulação do hardware
