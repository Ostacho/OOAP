using System;
using System.Collections.Generic;
using System.Net;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;

namespace lb11
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private async void LoadButton_Click(object sender, RoutedEventArgs e)
        {
            FilmList.Items.Clear();
            Log("▶️ Початок завантаження...");

            for (int page = 1; page <= 4; page++)
            {
                string url = page == 1 ? "https://uaserials.pro/films/" : $"https://uaserials.pro/films/page/{page}/";
                Log($"🌐 Переходимо на сторінку {url}");

                try
                {
                    string html = await DownloadPageAsync(url);
                    Log($"✅ Сторінка {page} завантажена");

                    var films = ParseFilms(html);

                    if (films.Count == 0)
                        Log("⚠️ Нічого не знайдено на сторінці");

                    FilmList.Items.Add(new FilmInfo
                    {
                        Title = $"========== СТОРІНКА {page} ==========",
                        IsSeparator = true
                    });

                    foreach (var film in films)
                    {
                        FilmList.Items.Add(film);
                    }

                }
                catch (Exception ex)
                {
                    Log($"❌ Помилка: {ex.Message}");
                }
            }

            Log("✅ Завантаження завершено.");
        }

        private async Task<string> DownloadPageAsync(string url)
        {
            using (WebClient client = new WebClient())
            {
                client.Headers.Add("User-Agent", "Mozilla/5.0");
                return await client.DownloadStringTaskAsync(url);
            }
        }

        private List<FilmInfo> ParseFilms(string html)
        {
            var list = new List<FilmInfo>();

            var regex = new Regex(
                "<div class=\"short-item.*?<img[^>]+src=\\\"(?<img>[^\\\"]+)\\\"[^>]*alt=\\\"(?<title>[^\\\"]+)\\\"",
                RegexOptions.Compiled | RegexOptions.Singleline);

            var matches = regex.Matches(html);

            foreach (Match match in matches)
            {
                string title = WebUtility.HtmlDecode(match.Groups["title"].Value.Trim());
                string imgSrc = match.Groups["img"].Value.StartsWith("http")
                    ? match.Groups["img"].Value
                    : $"https://uaserials.pro{match.Groups["img"].Value}";

                list.Add(new FilmInfo
                {
                    Title = title,
                    Image = new BitmapImage(new Uri(imgSrc))
                });
            }

            Log($"📦 Знайдено {list.Count} записів");
            return list;
        }

        private void Log(string message)
        {
            Dispatcher.Invoke(() =>
            {
                LogBox.AppendText($"{DateTime.Now:HH:mm:ss} | {message}\n");
                LogBox.ScrollToEnd();
            });
        }

        public class FilmInfo
        {
            public string Title { get; set; }
            public BitmapImage Image { get; set; }
            public bool IsSeparator { get; set; }

            public override string ToString()
            {
                return IsSeparator ? Title : $"🎬 {Title}";
            }
        }
    }
}