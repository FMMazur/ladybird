#pragma once

#include <LibWeb/Forward.h>
#include <AK/HashMap.h>
#include <LibWeb/Bindings/PlatformObject.h>

namespace Web::URLPattern {

struct URLPatternComponentResult {
    String input;
    OrderedHashMap<String, String> groups;
};

struct URLPatternInit {
    Optional<String> protocol;
    Optional<String> username;
    Optional<String> password;
    Optional<String> hostname;
    Optional<String> port;
    Optional<String> pathname;
    Optional<String> search;
    Optional<String> hash;
    Optional<String> base_url;
};

using URLPatternInput = Variant<String, URLPatternInit>;

struct URLPatternResult {
    Vector<URLPatternInput> inputs;

    URLPatternComponentResult protocol;
    URLPatternComponentResult username;
    URLPatternComponentResult password;
    URLPatternComponentResult hostname;
    URLPatternComponentResult port;
    URLPatternComponentResult pathname;
    URLPatternComponentResult search;
    URLPatternComponentResult hash;
};

struct URLPatternOptions {
  bool ignore_case = false;
};

class URLPattern : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(URLPattern, Bindings::PlatformObject);
    GC_DECLARE_ALLOCATOR(URLPattern);

    public:
        virtual ~URLPattern() override;
        [[nodiscard]] static GC::Ref<URLPattern> create(JS::Realm&, URLPatternInput, String base_url, URLPatternOptions = {});
        [[nodiscard]] static GC::Ref<URLPattern> create(JS::Realm&, Optional<URLPatternInput> = {}, Optional<URLPatternOptions> = {});

        static WebIDL::ExceptionOr<GC::Ref<URLPattern>> construct_impl(JS::Realm& realm, URLPatternInput, Optional<String> base_url, URLPatternOptions = {});
        static WebIDL::ExceptionOr<GC::Ref<URLPattern>> construct_impl(JS::Realm& realm, URLPatternInput, URLPatternOptions = {});

        bool test(Optional<URLPatternInput> = {}, Optional<String> base_url= {});

//        Optional<URLPatternResult> exec(Optional<URLPatternInput> = {}, Optional<String> base_url = {});
        URLPatternResult* exec(Optional<URLPatternInput> = {}, Optional<String> base_url = {});

        String const& protocol() const { return m_pattern.protocol.value(); }
        String const& username() const {return m_pattern.username.value(); };
        String const& password() const { return m_pattern.password.value(); };
        String const& hostname() const { return m_pattern.hostname.value(); };
        String const& port() const { return m_pattern.port.value(); };
        String const& pathname() const { return m_pattern.pathname.value(); };
        String const& search() const { return m_pattern.search.value(); };
        String const& hash() const { return m_pattern.hash.value(); };

        bool has_reg_exp_groups() const {
            TODO();
            return false;
        }

    private:
        URLPattern(JS::Realm&, URLPatternInit, URLPatternOptions);

        virtual void initialize(JS::Realm&) override;

        URLPatternInit m_pattern;
        URLPatternOptions m_options;
};

}