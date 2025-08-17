/*
* Minha calculadora feita em C
* @author : Adão Fernando Lufuma Ifafe 
* Sidadão : Angolano
* Para compilar o codigo sem ícone : gcc Calculadora.c -o Calculadora.exe -lgdi32 -mwindows  
* Para compilar com ícone :
* 1º Compile o recurso : windres resouce.rc -o resouce.o
* 2º Compile o recurso juntamente com o arquivo. c : gcc Calculadora.c resouce.o -o Calculadora.exe -lgdi32 -mwindows
*/ 
#include "MyMath.h" 

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void Caculator(HWND);
void addFunction(HWND);
void Calculate(const char *, HWND);
bool validarExpressao(const char *);
bool calculetorID(int);
bool validarOperator(int);
void initNewCalc();
void iscomplete(HWND);

HMENU hMenu;
HWND hr, hg, hb, hTextarea;
COLORREF corAtual = RGB(255,255,255);

char numeroText[SIZE_VETOR] = "\0", *controler1, *controler2, *controler3;
int sizeNumeroText, Riply, mathID = 0;
double riply;
bool expressaoCompleta, calcID;

WINAPI int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdL, int nCmdS) {
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "MyWindowsClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APP_ICON));

    if(!RegisterClass(&wc)) {
        MessageBox(NULL, "Failed to register window class", "Error", MB_ICONERROR);
        return 0;
    }
    HWND hWnd = CreateWindowEx(0, "MyWindowsClass", "Calc",
                                WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_POPUP,
                                CW_USEDEFAULT, CW_USEDEFAULT, 235, 500,
                                NULL, NULL, hInst, NULL);

    ShowWindow(hWnd, nCmdS);
    UpdateWindow(hWnd);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wPr, LPARAM lPr) {
    switch(uMsg) {
        case WM_COMMAND:
            switch(wPr) {
                case NELTRO_FUNCTION:
                    MessageBeep(MB_ICONINFORMATION);
                break;
                case EXITING_WINDOWS:
                    DestroyWindow(hWnd);
                break;
                case BUTTON_CALCULATOR:
                    expressaoCompleta = validarExpressao(numeroText);
                    if (expressaoCompleta == true) {
                        mathID = 0;
                        GetWindowText(hTextarea, numeroText, SIZE_VETOR);
                        Calculate(numeroText, hWnd);
                        SetWindowText(hTextarea, numeroText);
                        calcID = calculetorID(0);
                    }
                    else {
                        MessageBox(hWnd, "Erro dados a falta", "Error", MB_ICONERROR | WS_CHILD);
                    }
                break;
                case BUTTON_CLEAR:
                    strcpy(numeroText, "\0");         
                    SetWindowText(hTextarea, numeroText);
                    mathID = 0;
                break;
                case DARK_COLOR:
                    corAtual = (corAtual == RGB(255,255,255)) ? RGB(0,0,0) : RGB(0,0,0);
                    InvalidateRect(hWnd, NULL, TRUE);
                break;
                case LIGHT_COLOR: 
                    corAtual = (corAtual ==  RGB(0,0,0)) ? RGB(255,255,255) : RGB(255,255,255) ;
                    InvalidateRect(hWnd, NULL, TRUE);
                break;
                case BOTAO_QUAD:
                    GetWindowText(hTextarea, numeroText, SIZE_VETOR);
                    expressaoCompleta = validarExpressao(numeroText);
                    if (expressaoCompleta == true) {
                        Calculate(numeroText, hWnd);
                    }
                    if (numeroText[0] != '\0') { 
                        Riply = strtol(numeroText, &controler1, BASE_DECIMAL);
                        if (*controler1 == '\0') {
                            mathID = 0;
                            Riply = (int) quadrado((double)Riply);
                            sprintf(numeroText, "%d", Riply);
                            SetWindowText(hTextarea, numeroText);
                            calcID = calculetorID(0);
                        }
                        else {
                            MessageBox(hWnd, "Erro dados a falta", "Error", MB_ICONERROR | WS_CHILD);
                        }
                    }
                break;
                case BOTAO_PONT:
                    sizeNumeroText = strlen(numeroText);
                    iscomplete(hWnd);
                    if (numeroText[0] != '\0' && (numeroText[0] != '-'|| numeroText[0] == '-') && numeroText[sizeNumeroText] == '\0') { 
                        if (mathID == 0) {
                            if (mathID != '^' && numeroText[sizeNumeroText-2] != '^') {
                                mathID = 94;
                                strcat(numeroText, " ^ ");
                                SetWindowText(hTextarea, numeroText); 
                            }
                        }
                        else {
                            mathID = 94;
                            validarOperator(mathID);
                            SetWindowText(hTextarea, numeroText); 
                        }
                    }
                break;
                case BOTAO_REST:
                    GetWindowText(hTextarea, numeroText, SIZE_VETOR);
                    expressaoCompleta = validarExpressao(numeroText);
                    if (expressaoCompleta == true) {
                        Calculate(numeroText, hWnd);
                    }
                    if (numeroText[0] != '\0') { 
                        Riply = strtol(numeroText, &controler1, BASE_DECIMAL);
                        if (*controler1 == '\0') {
                            mathID = 0;
                            Riply = restFor2(Riply);
                            sprintf(numeroText, "%d", Riply);
                            SetWindowText(hTextarea, numeroText);
                            calcID = calculetorID(0);
                        } 
                    }
                break;
                case BOTAO_DELET:
                    sizeNumeroText = strlen(numeroText);
                    if (numeroText[sizeNumeroText-2] == '+' || (numeroText[sizeNumeroText-2] == '-' && numeroText[sizeNumeroText-3] == ' ') || numeroText[sizeNumeroText-2] == 'x' || numeroText[sizeNumeroText-2] == '/' || numeroText[sizeNumeroText-2] == '^') {
                        numeroText[sizeNumeroText-1] = '\0';
                        numeroText[sizeNumeroText-2] = '\0';
                        numeroText[sizeNumeroText-3] = '\0';
                        mathID = 0;
                    } 
                    numeroText[sizeNumeroText-1] = '\0';
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_PONTO:
                    sizeNumeroText = strlen(numeroText);
                    if (numeroText[0] != '\0' && (numeroText[0] != '-'|| numeroText[0] == '-') && numeroText[sizeNumeroText] == '\0') {
                        if (numeroText[sizeNumeroText-1] != '.') {
                            strcat(numeroText, ".");
                            SetWindowText(hTextarea, numeroText);
                        }
                    }
                break;
                case BOTAO_RAIZQ:
                    GetWindowText(hTextarea, numeroText, SIZE_VETOR);
                    expressaoCompleta = validarExpressao(numeroText);
                    if (expressaoCompleta == true) {
                        Calculate(numeroText, hWnd);
                    }
                    if (numeroText[0] != '\0') { 
                        riply = strtol(numeroText, &controler1, BASE_DECIMAL);
                        if (*controler1 == '\0') {
                            mathID = 0;
                            riply = raizQuadrada(riply);
                            sprintf(numeroText, "%.2f", riply);
                            strcpy(numeroText, aredondar(riply, numeroText, hWnd));
                            SetWindowText(hTextarea, numeroText);
                            calcID = calculetorID(0);
                        }
                    }
                break;
                case BOTAO_9:
                    initNewCalc();
                    strcat(numeroText, "9");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_8:
                    initNewCalc();
                    strcat(numeroText, "8");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_7:
                    initNewCalc();
                    strcat(numeroText, "7");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_6:
                    initNewCalc();
                    strcat(numeroText, "6");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_5:
                    initNewCalc();
                    strcat(numeroText, "5");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_4:
                    initNewCalc();
                    strcat(numeroText, "4");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_3:
                    initNewCalc();
                    strcat(numeroText, "3");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_2:
                    initNewCalc();
                    strcat(numeroText, "2");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_1:
                    initNewCalc(); 
                    strcat(numeroText, "1");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_0:
                    initNewCalc();
                    strcat(numeroText, "0");
                    SetWindowText(hTextarea, numeroText);
                break;
                case BOTAO_PLUS: 
                    sizeNumeroText = strlen(numeroText);
                    iscomplete(hWnd);
                    if (numeroText[0] != '\0' && (numeroText[0] != '-'|| numeroText[0] == '-') && numeroText[sizeNumeroText] == '\0') { 
                        if (mathID == 0) {
                            if (mathID != '+' && numeroText[sizeNumeroText-2] != '+') {
                                mathID = 43;
                                strcat(numeroText, " + ");
                                SetWindowText(hTextarea, numeroText);
                            }
                        }
                        else {
                            mathID = 43;
                            validarOperator(mathID);
                            SetWindowText(hTextarea, numeroText); 
                        }
                    }                    
                break;
                case BOTAO_SUBT:
                    sizeNumeroText = strlen(numeroText);
                    iscomplete(hWnd);
                    if (numeroText[0] != '\0' && (numeroText[0] != '-'|| numeroText[0] == '-') && numeroText[sizeNumeroText] == '\0') { 
                        if (mathID == 0) {
                            if (mathID != '-' && (numeroText[sizeNumeroText-2] != '-' || numeroText[sizeNumeroText-2] == '-')) {
                                mathID = 45;
                                strcat(numeroText, " - ");
                                SetWindowText(hTextarea, numeroText); 
                            }
                        }

                        else {
                            mathID = 45;
                            validarOperator(mathID);
                            SetWindowText(hTextarea, numeroText); 
                        }
                    }
                    else if (numeroText[0] == '\0') {
                        strcat(numeroText, "-");
                        SetWindowText(hTextarea, numeroText);
                    }
                break;
                case BOTAO_VESES:
                    sizeNumeroText = strlen(numeroText);
                    iscomplete(hWnd);
                    if (numeroText[0] != '\0' && (numeroText[0] != '-'|| numeroText[0] == '-') && numeroText[sizeNumeroText] == '\0') { 
                        if (mathID == 0) {
                            if (mathID != 'x' && numeroText[sizeNumeroText-2] != 'x') {
                                mathID = 120;
                                strcat(numeroText, " x ");
                                SetWindowText(hTextarea, numeroText);
                            }
                        }
                        else {
                            mathID = 120;
                            validarOperator(mathID);
                            SetWindowText(hTextarea, numeroText); 
                        }
                    }
                break;
                case BOTAO_DIVIS:
                    sizeNumeroText = strlen(numeroText);
                    iscomplete(hWnd);
                    if (numeroText[0] != '\0' && (numeroText[0] != '-' || numeroText[0] == '-') && numeroText[sizeNumeroText] == '\0') {
                        if (mathID == 0) {
                            if (mathID != '/' && numeroText[sizeNumeroText-2] != '/') {
                                mathID = 47;
                                strcat(numeroText, " / ");
                                SetWindowText(hTextarea, numeroText);
                            }
                        }
                        else {
                            mathID = 47;
                            validarOperator(mathID);
                            SetWindowText(hTextarea, numeroText); 
                        }
                    }
                break;
                case BOTAO_ABRE_PAREN:
                break;
                case BOTAO_FECHA_PAREN:
                break;
            }
        break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBRUSH hBrush = CreateSolidBrush(corAtual);
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_CREATE:
            addFunction(hWnd);
            Caculator(hWnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        break;
        default:
            return DefWindowProc(hWnd, uMsg, wPr, lPr);
        break;
    }
    return 0;
}

void Caculator(HWND hWnd) {
    //Esta parte é o local do texto.
    hTextarea = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | WS_BORDER | WS_BORDER, 0, 0, 235, 105, hWnd, NULL, NULL, NULL);

    //Botões propriedade extras
    CreateWindowW(L"button", L"^2", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 5, 120, 50, 50, hWnd, (HMENU)BOTAO_QUAD, NULL, NULL);
    CreateWindowW(L"button", L"%", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 58, 120, 50, 50, hWnd, (HMENU)BOTAO_REST, NULL, NULL);
    CreateWindowW(L"button", L"Clean", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 111, 120, 50, 50, hWnd, (HMENU)BUTTON_CLEAR, NULL, NULL);
    CreateWindowW(L"button", L"^x", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 5, 172, 50, 50, hWnd, (HMENU)BOTAO_PONT, NULL, NULL);
    CreateWindowW(L"button", L".", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 58, 172, 50, 50, hWnd, (HMENU)BOTAO_PONTO, NULL, NULL);
    CreateWindowW(L"button", L"Vx", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 111, 172, 50, 50, hWnd, (HMENU)BOTAO_RAIZQ, NULL, NULL);

    //Botões numéricos
    CreateWindowW(L"button", L"7", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 5, 224, 50, 50, hWnd, (HMENU)BOTAO_7, NULL, NULL);
    CreateWindowW(L"button", L"8", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 58, 224, 50, 50, hWnd, (HMENU)BOTAO_8, NULL, NULL);
    CreateWindowW(L"button", L"9", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 111, 224, 50, 50, hWnd, (HMENU)BOTAO_9, NULL, NULL);
    CreateWindowW(L"button", L"6", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 5, 276, 50, 50, hWnd, (HMENU)BOTAO_6, NULL, NULL);
    CreateWindowW(L"button", L"5", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 58, 276, 50, 50, hWnd, (HMENU)BOTAO_5, NULL, NULL);
    CreateWindowW(L"button", L"4", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 111, 276, 50, 50, hWnd, (HMENU)BOTAO_4, NULL, NULL);
    CreateWindowW(L"button", L"3", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 5, 328, 50, 50, hWnd, (HMENU)BOTAO_3, NULL, NULL);
    CreateWindowW(L"button", L"2", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 58, 328, 50, 50, hWnd, (HMENU)BOTAO_2, NULL, NULL);
    CreateWindowW(L"button", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 111, 328, 50, 50, hWnd, (HMENU)BOTAO_1, NULL, NULL);
    CreateWindowW(L"button", L"(", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 5, 380, 50, 50, hWnd, (HMENU)BOTAO_ABRE_PAREN, NULL, NULL);
    CreateWindowW(L"button", L"0", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 58, 380, 50, 50, hWnd, (HMENU)BOTAO_0, NULL, NULL);
    CreateWindowW(L"button", L")", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 111, 380, 50, 50, hWnd, (HMENU)BOTAO_FECHA_PAREN, NULL, NULL);

    //Botões de operadores
    CreateWindowW(L"button", L"«x", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 163, 120, 50, 50, hWnd, (HMENU)BOTAO_DELET, NULL, NULL);
    CreateWindowW(L"button", L"/", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 163, 172, 50, 50, hWnd, (HMENU)BOTAO_DIVIS, NULL, NULL);
    CreateWindowW(L"button", L"X", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 163, 224, 50, 50, hWnd, (HMENU)BOTAO_VESES, NULL, NULL);
    CreateWindowW(L"button", L"-", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 163, 276, 50, 50, hWnd, (HMENU)BOTAO_SUBT, NULL, NULL);
    CreateWindowW(L"button", L"+", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 163, 328, 50, 50, hWnd, (HMENU)BOTAO_PLUS, NULL, NULL);
    CreateWindowW(L"button", L"=", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_BORDER, 163, 380, 50, 50, hWnd, (HMENU)BUTTON_CALCULATOR, NULL, NULL);
    
}

void addFunction(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSettings = CreateMenu();
    HMENU hEdit = CreateMenu();

    AppendMenu(hFileMenu, MF_STRING, NELTRO_FUNCTION, "Conversao de base");
    AppendMenu(hFileMenu, MF_STRING, NELTRO_FUNCTION, "Historico");
    AppendMenu(hFileMenu, MF_SEPARATOR, OBSULET_FUNCTION, NULL);
    AppendMenu(hFileMenu, MF_STRING, EXITING_WINDOWS, "EXIT");

    AppendMenu(hEdit, MF_STRING, DARK_COLOR, "DARK");
    AppendMenu(hEdit, MF_STRING, LIGHT_COLOR, "LIGHT");
    AppendMenu(hEdit, MF_SEPARATOR, OBSULET_FUNCTION, NULL);
    AppendMenu(hEdit, MF_STRING, ID_BTN_COR, "CREATE YOUR COLOR");

    AppendMenu(hSettings, MF_POPUP, (UINT_PTR)hEdit, "SET COLOR");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "   FILE   ");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSettings, "SETTINGS");

    SetMenu(hWnd, hMenu);
}

void Calculate(const char *expressao, HWND hWnd) {
    int Num1, Num2; 
    char Operator;
    sscanf(expressao, "%d %c %d", &Num1, &Operator, &Num2);
    if (Operator == '+') {
        Riply = (int)somador((double)Num1, (double)Num2);
        sprintf(numeroText, "%d", Riply);
    }
    else if (Operator == '-') {
        Riply = (int)subtract((double)Num1, (double)Num2);
        sprintf(numeroText, "%d", Riply);
    }
    else if (Operator == 'x') {
        Riply = (int)mult((double)Num1, (double)Num2);
        sprintf(numeroText, "%d", Riply);
    }
    else if (Operator == '/') {
        riply = divis((double)Num1, (double)Num2);
        sprintf(numeroText, "%.2f", riply);
        strcpy(numeroText, aredondar(riply, numeroText, hWnd));
    }
    else if (Operator == '^') {
        Riply = (int)potencia((double)Num1, (double)Num2);
        sprintf(numeroText, "%d", Riply);
    }
    return;
}

bool validarExpressao(const char *expressao){
    int num1 = 0, num2 = 0;
    char chart = '\0';
    sscanf(expressao, "%d %c %d", &num1, &chart, &num2);
    if (num1 != 0 && chart != '\0' && num2 != 0) {
        return true;
    }
    return false;
}

bool calculetorID(int idProc) {
    if (idProc == 0) {
        return true;
    }
    return false;
}

bool validarOperator(int operatorID) {
    sizeNumeroText = strlen(numeroText);
    numeroText[sizeNumeroText-2] = operatorID;
    return true;
}

void initNewCalc() {
    sizeNumeroText = strlen(numeroText);
    if (calcID == true && (numeroText[sizeNumeroText-2] != '+' && (numeroText[sizeNumeroText-2] != '-' && numeroText[sizeNumeroText-3] != ' ') && numeroText[sizeNumeroText-2] != 'x' && numeroText[sizeNumeroText-2] != '/' && numeroText[sizeNumeroText-2] != '^')) {
        strcpy(numeroText, "");
        SetWindowText(hTextarea, numeroText);
        calcID = false;
    }
    else {
        calcID = false;
    }
    return;
}

void iscomplete(HWND hWnd) {
    expressaoCompleta = validarExpressao(numeroText);
    if (expressaoCompleta == true) {
        Calculate(numeroText, hWnd);
        mathID = 0;
        SetWindowText(hTextarea, numeroText);
    }
}
