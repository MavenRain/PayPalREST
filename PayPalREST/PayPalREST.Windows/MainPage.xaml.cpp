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


void PayPalREST::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	String^ bufferString = CryptographicBuffer::EncodeToBase64String(CryptographicBuffer::ConvertStringToBinary(ref new String(L"AXVXPhBYtwEl_oJV1U8BohrSTFUG7A8IPOpYLaP3A_30cZ7L_w94r3G2gvsa:EJQ_ZhBDtIGpd1yGmtDsKyihcfcQ_9dzpHXjaTSVX39Li7zP91kiBkd8BiJk"), BinaryStringEncoding::Utf8));
	Uri^ uri = ref new Uri(ref new String(L"https://api.sandbox.paypal.com/v1/oauth2/token"));
	HttpRequestMessage^ request = ref new HttpRequestMessage(HttpMethod::Post,uri);
	request->Headers->Append("Accept", "application/json");
	request->Headers->Authorization = ref new HttpCredentialsHeaderValue("Basic", bufferString);
	Map<String^, String^>^ iMap = ref new Map<String^, String^>();
	iMap->Insert(ref new String(L"grant_type"), ref new String(L"client_credentials"));
	iMap->Insert(ref new String(L"content-type"), ref new String(L"application/x-www-form-urlencoded"));
	request->Content = ref new HttpFormUrlEncodedContent(iMap);
	HttpClient^ httpClient = ref new HttpClient();
	create_task(httpClient->SendRequestAsync(request)).then([this](HttpResponseMessage^ response)
	{
		JsonObject^ jsonObject = JsonObject::Parse(response->Content->ReadAsStringAsync()->GetResults()); 
		String^ accessToken = jsonObject->GetNamedString("access_token", "");
		Uri^ uri = ref new Uri(ref new String(L"https://api.sandbox.paypal.com/v1/identity/openidconnect/userinfo/?schema=openid"));
		HttpRequestMessage^ request = ref new HttpRequestMessage(HttpMethod::Post, uri);
		request->Headers->Authorization = ref new HttpCredentialsHeaderValue("Bearer", accessToken);
		/*
		Map<String^, String^>^ iMap = ref new Map<String^, String^>();
		iMap->Insert(ref new String(L"content-type"), ref new String(L"application/json"));
		String^ jsonContent = ref new String(L"{\"intent\":\"sale\"},\"payer\":{\"payment_method\":\"paypal\"},\"transactions\":[{\"amount\":{\"total\":\"1\",\"currency\":\"USD\"}}]}");
		request->Content = ref new HttpStringContent(jsonContent);
		*/
		HttpClient^ httpClient = ref new HttpClient();
		create_task(httpClient->SendRequestAsync(request)).then([this](HttpResponseMessage^ response)
		{
			_response->Text = JsonObject::Parse(response->Content->ReadAsStringAsync()->GetResults())->GetNamedString("name", "");
		});
	}, task_continuation_context::use_current());
}
