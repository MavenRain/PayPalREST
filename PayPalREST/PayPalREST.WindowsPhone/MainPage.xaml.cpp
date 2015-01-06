//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter

	// TODO: Prepare page for display here.

	// TODO: If your application contains multiple pages, ensure that you are
	// handling the hardware Back button by registering for the
	// Windows::Phone::UI::Input::HardwareButtons.BackPressed event.
	// If you are using the NavigationHelper provided by some templates,
	// this event is handled for you.
}


void PayPalREST::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	String^ bufferString = CryptographicBuffer::EncodeToBase64String(CryptographicBuffer::ConvertStringToBinary(ref new String(L"AXVXPhBYtwEl_oJV1U8BohrSTFUG7A8IPOpYLaP3A_30cZ7L_w94r3G2gvsa:EJQ_ZhBDtIGpd1yGmtDsKyihcfcQ_9dzpHXjaTSVX39Li7zP91kiBkd8BiJk"), BinaryStringEncoding::Utf8));
	Uri^ uri = ref new Uri(ref new String(L"https://api.sandbox.paypal.com/v1/oauth2/token"));
	HttpRequestMessage^ request = ref new HttpRequestMessage(HttpMethod::Post, uri);
	request->Headers->Append("Accept", "application/json");
	request->Headers->Authorization = ref new HttpCredentialsHeaderValue("Basic", bufferString);
	Map<String^, String^>^ iMap = ref new Map<String^, String^>();
	iMap->Insert(ref new String(L"grant_type"), ref new String(L"client_credentials"));
	iMap->Insert(ref new String(L"content-type"), ref new String(L"application/x-www-form-urlencoded"));
	request->Content = ref new HttpFormUrlEncodedContent(iMap);
	HttpClient^ httpClient = ref new HttpClient();
	create_task(httpClient->SendRequestAsync(request)).then([this](HttpResponseMessage^ response){_response->Text = response->Content->ReadAsStringAsync()->GetResults(); }, task_continuation_context::use_current());
}
