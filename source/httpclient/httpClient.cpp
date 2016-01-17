
#include <raumkernel/httpclient/httpClient.h>

namespace Raumkernel
{
    namespace HttpClient
    {
        HttpClient::HttpClient() : RaumkernelBase()
        {          
        }


        HttpClient::~HttpClient()
        {
        }


        void HttpClient::test()
        { 

            struct mg_mgr mgr;
            int i;

            // HTTPCLientEvHandlerData -> HTTPClientInstance
            // HTTPCLientEvHandlerData -> uniqueNumber of request (for clsoing request)
            // HTTPCLientEvHandlerData -> UserData
            

            mg_mgr_init(&mgr, "!!!UserData!!!");

            /*
        
            for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], s_show_headers_opt) == 0) {
                    s_show_headers = 1;
                }
                else if (strcmp(argv[i], "--hexdump") == 0 && i + 1 < argc) {
                    mgr.hexdump_file = argv[++i];
                }
                else {
                    break;
                }
            }

            if (i + 1 != argc) {
                fprintf(stderr, "Usage: %s [%s] [--hexdump <file>] <URL>\n",
                    argv[0], s_show_headers_opt);
                exit(EXIT_FAILURE);
            }
            */
           
            s_exit_flag = 0;
            
            
            mg_connect_http(&mgr, &HttpClient::ev_handler, "10.0.0.5:47365/getZones", NULL, NULL);
            //mg_connect_http(&mgr, &HttpClient::ev_handler, "www.google.at", NULL, NULL);

            while (s_exit_flag == 0) {
                mg_mgr_poll(&mgr, 1000);
            }
            mg_mgr_free(&mgr);
        }

        void HttpClient::ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
            struct http_message *hm = (struct http_message *) ev_data;

            // TODDI: Lock
            // evData may hold class reference?!

            switch (ev) {
            case MG_EV_CONNECT:
                if (*(int *)ev_data != 0) {
                    fprintf(stderr, "connect() failed: %s\n", strerror(*(int *)ev_data));
                    //s_exit_flag = 1;
                }
                break;
            case MG_EV_HTTP_REPLY:
                nc->flags |= MG_F_CLOSE_IMMEDIATELY;
                //if (s_show_headers) {
                //    fwrite(hm->message.p, 1, hm->message.len, stdout);
               // }
               // else {
                    fwrite(hm->body.p, 1, hm->body.len, stdout);
                //}
                putchar('\n');
                //s_exit_flag = 1;
                break;
            default:
                break;
            }
        }
    }
}