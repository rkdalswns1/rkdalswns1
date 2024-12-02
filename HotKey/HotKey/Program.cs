using System;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace GlobalTextConverter
{
    public partial class MainForm : Form
    {
        // 글로벌 핫키 등록용 상수 및 메서드 선언
        [DllImport("user32.dll")]
        private static extern bool RegisterHotKey(IntPtr hWnd, int id, uint fsModifiers, uint vk);

        [DllImport("user32.dll")]
        private static extern bool UnregisterHotKey(IntPtr hWnd, int id);

        private const int HOTKEY_ID = 9000; // Arbitrary ID for the hotkey

        public MainForm()
        {
            InitializeComponent();
            RegisterHotKey(this.Handle, HOTKEY_ID, (uint)ModifierKeys.Control, (uint)Keys.HanjaMode);
        }

        // 핫키 이벤트 처리
        protected override void WndProc(ref Message m)
        {
            const int WM_HOTKEY = 0x0312;
            if (m.Msg == WM_HOTKEY && m.WParam.ToInt32() == HOTKEY_ID)
            {
                ProcessTextConversion();
            }
            base.WndProc(ref m);
        }

        private void ProcessTextConversion()
        {
            // 드래그한 텍스트 가져오기 (여기서는 TextBox 코드 예제)
            string selectedText = GetSelectedText();

            // 변환 예제 (영어 <-> 한국어)
            string convertedText = ConvertText(selectedText);

            // 변환된 텍스트로 교체하기
            ReplaceSelectedText(convertedText);
        }

        private string GetSelectedText()
        {
            // 예시: TextBox에서 선택된 텍스트 가져오기
            return this.textBox1.SelectedText;
        }

        private void ReplaceSelectedText(string text)
        {
            // 예시: TextBox에서 선택된 텍스트를 변환 텍스트로 바꾸기
            int selectionIndex = this.textBox1.SelectionStart;
            this.textBox1.Text = this.textBox1.Text.Remove(selectionIndex, this.textBox1.SelectionLength);
            this.textBox1.Text = this.textBox1.Text.Insert(selectionIndex, text);
        }

        private string ConvertText(string text)
        {
            // 한글과 영어 문자 변환 예제
            // 실제 키 매핑 로직 필요
            return text; // 변환 로직을 여기에 추가하세요
        }

        protected override void OnClosed(EventArgs e)
        {
            UnregisterHotKey(this.Handle, HOTKEY_ID);
            base.OnClosed(e);
        }
    }
}