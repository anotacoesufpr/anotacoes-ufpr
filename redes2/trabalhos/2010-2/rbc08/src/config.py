# *-* coding: utf-8 *-*

## Arquivo com definições de variáveis e constantes usadas no trabalho
# @file config.py

## Nome do arquivo de log do cliente
CLIENT_LOG_FILENAME = "cliente.log"

## Nome do arquivo de log do servidor
SERVER_LOG_FILENAME = "servidor.log"

## Nome do arquivo de log de eventos
EVENT_LOG_FILENAME = "eventos.log"

## path para o arquivo HTML da interface gráfica
GUI_FILENAME = "gui.html"

## Comando para abrir o navegador para mostrar a interface gráfica
# {0} => nome do arquivo HTML da GUI
GUI_CMD = "chromium-browser {0} 2> /dev/null &"


## constante que indica host Desconhecido
HOST_DESCONHECIDO = "Desconhecido"
## constante que indica host Ativo
HOST_ATIVO = "Ativo"
## constante que indica host Falho
HOST_FALHO = "Falho"

## Cor, em hexa, para host no estado Desconhecido
COR_HOST_DESCONHECIDO = '#666666'
## Cor, em hexa, para host no estado Ativo
COR_HOST_ATIVO = '#006400'
## Cor, em hexa, para host no estado Falho
COR_HOST_FALHO = '#FF0000'


## Tamanho máximo, em bytes, a ser recebido do socket ( usado em socket.recv() )
MAX_RECV_SIZE = 4096

## Intervalo de tempo, em segundos, a aguardar antes de verificar novamente os estados dos hosts
PING_INTERVAL = 5


## quantidade de tentativas de PING antes de considerar um host com falho ou inativo
PING_COUNT = 4


##
# Valores para o campo "codigo" da mensagem, segundo o protocolo da aplicação

## Código correspondente a envio de lista de hosts
PROTOCOL_COD_SEND_HOSTS = 0

## Código para informar mudança de estado (evento)
PROTOCOL_COD_EVENT = 1

## Separador de hosts usado no envio da lista de hosts ao monitor
HOSTS_SEP = "|"


##
# Padrão das mensagens enviadas ao cliente e inseridas no log
# Os números entre chaves são trocados pelos parâmetros corretos, com o método
# format() da classe string, semelhante a um printf no C/C++

## Mensagem para informar tentativa de resolução de DNS
# {0} => DNS
MSG_RESOLV_DNS = "Resolvendo DNS do host {0} ..."

## Falha ao resolver DNS
# {0} => DNS
MSG_RESOLV_DNS_FAIL = "Impossível resolver DNS do host {0}"

## DNS resolvido com sucesso
# {0} => DNS, {1} => IP
MSG_RESOLV_DNS_SUCCESS = "Resolvido DNS do host {0} para o {1}"

## Tentativa de ping
# {0] => IP do host
MSG_PING = "Realizando ping no host {0} ..."

## Retorno do ping ao host
# {0} => IP do host, {1} => retorno do PING
MSG_RES_PING = "Retorno do PING ao host {0} : {1}"

## Informa a ocorrência de um evento (mudança de estado de host)
# {0} => DNS, {1} => IP, {2} => estado anterior, {3} => novo estado
MSG_EVENT = "Mudança de estado do host {0} ({1}): de {2} para {3}"




