#include "UrlPattern.h"

#include <LibJS/Runtime/Realm.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::URLPattern {
	GC_DEFINE_ALLOCATOR(URLPattern);

	URLPattern::URLPattern(JS::Realm& realm, URLPatternInit init, URLPatternOptions options)
            : PlatformObject(realm)
            , m_pattern(move(init))
        	, m_options(move(options))
        {}

    URLPattern::~URLPattern() = default;

	void URLPattern::initialize(JS::Realm& realm) {
            Base::initialize(realm);
            WEB_SET_PROTOTYPE_FOR_INTERFACE(URLPattern);
    }

    GC::Ref<URLPattern> URLPattern::create(JS::Realm& realm, URLPatternInput input, String base_url, URLPatternOptions options)
    {
        dbgln("Creating URLPattern 1");
        return realm.create<URLPattern>(realm, move(input), move(options));
    }

    GC::Ref<URLPattern> URLPattern::create(JS::Realm& realm, Optional<URLPatternInput> input, Optional<URLPatternOptions> options) {
        dbgln("Creating URLPattern 2");
        return realm.create<URLPattern>(realm, move(input), move(options));
    }

    WebIDL::ExceptionOr<GC::Ref<URLPattern>> URLPattern::construct_impl(JS::Realm& realm, URLPatternInput input, URLPatternOptions options) {
        return construct_impl(realm, input, {}, options);
    }

    WebIDL::ExceptionOr<GC::Ref<URLPattern>> URLPattern::construct_impl(JS::Realm& realm, URLPatternInput input, Optional<String> base_url, URLPatternOptions options)
	{
		//          (void)  URLPattern::construct_impl(realm, input, ""sv, options);
    	//1. Let init be null.
		URLPatternInit init;

      	//2. If input is a scalar value string then:
        if (input.has<String>()) {
            //1. Set init to the result of running parse a constructor string given input.
			//2. If baseURL is null and init["protocol"] does not exist, then throw a TypeError.
			//3. If baseURL is not null, set init["baseURL"] to baseURL.
        }
        //3. Otherwise:
        else {
			//1. Assert: input is a URLPatternInit.
            VERIFY(input.has<URLPatternInit>());
			//2. If baseURL is not null, then throw a TypeError.
            if (base_url.has_value()) {
                return Web::WebIDL::SimpleException { WebIDL::SimpleExceptionType::TypeError, "FIXME: add error message"sv };
            }
			//3. Set init to input.
            init = input.get<URLPatternInit>();
        }
        //4. Let processedInit be the result of process a URLPatternInit given init, "pattern", null, null,
        //null, null, null, null, null, and null.
        //5. For each componentName of « "protocol", "username", "password", "hostname",
        //"port", "pathname", "search", "hash" »:
        //1. If processedInit[componentName] does not exist,
        //then set processedInit[componentName] to "*".
        //6. If processedInit["protocol"] is a special scheme and processedInit["port"] is a string
        //which represents its corresponding default port in radix-10 using ASCII digits then
        //set processedInit["port"] to the empty string.
        //7. Let urlPattern be a new URL pattern.
        //8. Set urlPattern’s protocol component to the result of compiling a
        //component given processedInit["protocol"], canonicalize a protocol, and default options.
        //9. Set urlPattern’s username component to the result of compiling a
        //component given processedInit["username"], canonicalize a username, and default options.
        //10. Set urlPattern’s password component to the result of compiling a
        //component given processedInit["password"], canonicalize a password, and default options.
        //11. If the result running hostname pattern is an IPv6 address given processedInit["hostname"] is
        //true, then set urlPattern’s hostname component to the result of compiling a
        //component given processedInit["hostname"], canonicalize an IPv6 hostname,
        //and hostname options.
        //12. Otherwise, set urlPattern’s hostname component to the result of compiling a
        //component given processedInit["hostname"], canonicalize a hostname, and hostname
        //options.
        //13. Set urlPattern’s port component to the result of compiling a
        //component given processedInit["port"], canonicalize a port, and default options.
    	return create(realm, init, move(options));
	}

    bool URLPattern::test(Optional<URLPatternInput> input, Optional<String> base_url) {
        (void) input;
        (void) base_url;
        TODO();
        return false;
    }

    URLPatternResult* URLPattern::exec(Optional<URLPatternInput> input, Optional<String> base_url ) {
        (void) input;
        (void) base_url;
        TODO();
        return nullptr;
    }
}